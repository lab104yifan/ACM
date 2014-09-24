#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXNODE = 105 * 2;
const int MAXEDGE = 100005;

typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge {
	int u, v;
	Type cap, flow;
	Edge() {}
	Edge(int u, int v, Type cap, Type flow) {
		this->u = u;
		this->v = v;
		this->cap = cap;
		this->flow = flow;
	}
};

struct Dinic {
	int n, m, s, t;
	Edge edges[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	bool vis[MAXNODE];
	Type d[MAXNODE];
	int cur[MAXNODE];

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}
	void add_Edge(int u, int v, Type cap) {
		edges[m] = Edge(u, v, cap, 0);
		next[m] = first[u];
		first[u] = m++;
		edges[m] = Edge(v, u, 0, 0);
		next[m] = first[v];
		first[v] = m++;
	}

	bool bfs() {
		memset(vis, false, sizeof(vis));
		queue<int> Q;
		Q.push(s);
		d[s] = 0;
		vis[s] = true;
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (!vis[e.v] && e.cap > e.flow) {
					vis[e.v] = true;
					d[e.v] = d[u] + 1;
					Q.push(e.v);
				}
			}
		}
		return vis[t];
	}

	Type dfs(int u, Type a) {
		if (u == t || a == 0) return a;
		Type flow = 0, f;
		for (int &i = cur[u]; i != -1; i = next[i]) {
			Edge& e = edges[i];
			if (d[u] + 1 == d[e.v] && (f = dfs(e.v, min(a, e.cap - e.flow))) > 0) {
				e.flow += f;
				edges[i^1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		return flow;
	}

	Type Maxflow(int s, int t) {
		this->s = s; this->t = t;
		Type flow = 0;
		while (bfs()) {
			for (int i = 0; i < n; i++)
				cur[i] = first[i];
			flow += dfs(s, INF);
		}
		return flow;
	}
} gao;

const int N = 105;

int t, n, m, ans[N][N];

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		gao.init(n + m + 2);
		int pre = 0, tmp;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &tmp);
			gao.add_Edge(0, i, tmp - pre - m);
			pre = tmp;
		}
		pre = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%d", &tmp);
			gao.add_Edge(i + n, n + m + 1, tmp - pre - n);
			pre = tmp;
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				gao.add_Edge(i, j + n, 19);
		gao.Maxflow(0, n + m + 1);
		printf("Matrix %d\n", ++cas);
		for (int i = 1; i <= n; i++) {
			for (int j = gao.first[i]; j != -1; j = gao.next[j]) {
				Edge e = gao.edges[j];
	 			if (e.v > n && e.v <= n + m)
					ans[i][e.v - n] = e.flow;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				printf("%d%c", ans[i][j] + 1, j == m ? '\n' : ' ');
		}
	}
	return 0;
}

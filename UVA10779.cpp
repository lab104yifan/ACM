#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXNODE = 1005;
const int MAXEDGE = 100005;

const int INF = 0x3f3f3f3f;

struct Edge {
	int u, v, cap, flow;
	Edge() {}
	Edge(int u, int v, int cap, int flow) {
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
	int d[MAXNODE];
	int cur[MAXNODE];

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}

	void add_Edge(int u, int v, int cap) {
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

	int dfs(int u, int a) {
		if (u == t || a == 0) return a;
		int flow = 0, f;
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

	int Maxflow(int s, int t) {
		this->s = s;
		this->t = t;
		int flow = 0;
		while (bfs()) {
			for (int i = 0; i < n; i++)
				cur[i] = first[i];
			flow += dfs(s, INF);
		}
		return flow;
	}
} gao;

const int N = 30;

int T, n, m, cnt[N];

int main() {
	int cas = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		int s = 0, t = n + m;
		gao.init(t + 1);
		for (int i = 0; i < n; i++) {
			int tot, tmp;
			memset(cnt, 0, sizeof(cnt));
			scanf("%d", &tot);
			while (tot--) {
				scanf("%d", &tmp);
				cnt[tmp]++;
			}
			if (i == 0) {
				for (int j = 1; j <= m; j++)
					if (cnt[j] > 0) gao.add_Edge(i, j + n - 1, cnt[j]);
			} else {
				for (int j = 1; j <= m; j++) {
					if (cnt[j] > 1) gao.add_Edge(i, j + n - 1, cnt[j] - 1);
					if (cnt[j] == 0) gao.add_Edge(j + n - 1, i, 1);
				}
			}
		}
		for (int i = 1; i <= m; i++)
			gao.add_Edge(i + n - 1, t, 1);
		printf("Case #%d: %d\n", ++cas, gao.Maxflow(s, t));
	}
	return 0;
}

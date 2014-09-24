#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXNODE = 105 * 2;
const int MAXEDGE = 100005;

typedef int Type;
const Type INF = 0x3f3f3f3f;

int n, m, c;

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

bool cmp(Edge a, Edge b) {
	if (a.u != b.u) return a.u < b.u;
	return a.v < b.v;
}

struct Dinic {
	int n, m, s, t;
	Edge edges[MAXEDGE], etmp[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	bool vis[MAXNODE];
	Type d[MAXNODE];
	int cur[MAXNODE];
	vector<int> cut;
	vector<Edge> ans;
	Type flow;

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
		flow = 0;
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

	void MinCut() {
		cut.clear();
		for (int i = 0; i < m; i += 2) {
			if (vis[edges[i].u] && !vis[edges[i].v])
				cut.push_back(i);
		}
	}

	bool Maxflow(int s, int t) {
		this->s = s; this->t = t;
		while (bfs()) {
			for (int i = 0; i < n; i++)
				cur[i] = first[i];
			flow += dfs(s, INF);
			if (flow >= c) return true;
		}
		return false;
	}

	void solve() {
		if (Maxflow(0, n - 1) || c == 0) printf("possible\n");
		else {
			MinCut();
			ans.clear();
			for (int i = 0; i < m; i++)
				etmp[i] = edges[i];
			int tmpf = flow;
			for (int i = 0; i < cut.size(); i++) {
				edges[cut[i]].cap = edges[cut[i]].flow + c;
				if (Maxflow(0, n - 1)) ans.push_back(edges[cut[i]]);
				flow = tmpf;
				for (int i = 0; i < m; i++)
					edges[i] = etmp[i];
			}
			if (ans.size() == 0) printf("not possible\n");
			else {
				sort(ans.begin(), ans.end(), cmp);
				printf("possible option:");
				for (int i = 0; i < ans.size(); i++)
					printf("(%d,%d)%c", ans[i].u + 1, ans[i].v + 1, i == ans.size() - 1 ? '\n' : ',');
			}
		}
	}
} gao;

int main() {
	int cas = 0;
	while (~scanf("%d%d%d", &n, &m, &c) && n) {
		gao.init(n);
		int u, v, cap;
		while (m--) {
			scanf("%d%d%d", &u, &v, &cap);
			u--; v--;
			gao.add_Edge(u, v, cap);
		}
		printf("Case %d: ", ++cas);
		gao.solve();
	}
	return 0;
}

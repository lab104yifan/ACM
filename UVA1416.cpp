#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f3f3f3f

typedef long long ll;
const int MAXNODE = 105;

struct Edge {
	int u, v;
	ll dist;
	Edge() {}
	Edge(int u, int v, ll dist) {
		this->u = u;
		this->v = v;
		this->dist = dist;
	}
};

struct HeapNode {
	ll d;
	int u;
	HeapNode() {}
	HeapNode(ll d, int u) {
		this->d = d;
		this->u = u;
	}
	bool operator < (const HeapNode& c) const {
		return d > c.d;
	}
};

struct Dijkstra {
	int n, m;
	vector<Edge> edges;
	vector<int> g[MAXNODE];
	bool done[MAXNODE];
	ll d[MAXNODE];
	int p[MAXNODE];

	void init(int tot) {
		n = tot;
		for (int i = 0; i < n; i++)
			g[i].clear();
		edges.clear();
	}

	void add_Edge(int u, int v, ll dist) {
		edges.push_back(Edge(u, v, dist));
		m = edges.size();
		g[u].push_back(m - 1);
	}

	void print(int e) {//shun xu
		if (p[e] == -1) {
			printf("%d", e + 1);
			return;
		}
		print(edges[p[e]].u);
		printf(" %d", e + 1);
	}

	void print2(int e) {//ni xu
		if (p[e] == -1) {
			printf("%d\n", e + 1);
			return;
		}
		printf("%d ", e + 1);
		print2(edges[p[e]].u);
	}

	void dijkstra(int s) {
		priority_queue<HeapNode> Q;
		for (int i = 0; i < n; i++) d[i] = INF;
		d[s] = 0;
		p[s] = -1;
		memset(done, false, sizeof(done));
		Q.push(HeapNode(0, s));
		while (!Q.empty()) {
			HeapNode x = Q.top(); Q.pop();
			int u = x.u;
			if (done[u]) continue;
			done[u] = true;
			for (int i = 0; i < g[u].size(); i++) {
				Edge& e = edges[g[u][i]];
				if (d[e.v] > d[u] + e.dist) {
					d[e.v] = d[u] + e.dist;
					p[e.v] = g[u][i];
					Q.push(HeapNode(d[e.v], e.v));
				}
			}
		}
	}
} gao, gao2;

const int M = 1005;

int n, m;
ll L, c[M];
Edge e[M];

int main() {
	while (~scanf("%d%d%lld", &n, &m, &L)) {
		gao.init(n);
		int u, v;
		ll dist;
		for (int i = 0; i < m; i++) {
			scanf("%d%d%lld", &u, &v, &dist);
			u--; v--;
			e[i] = Edge(u, v, dist);
			gao.add_Edge(u, v, dist);
			gao.add_Edge(v, u, dist);
		}
		memset(c, 0, sizeof(c));
		ll ans1 = 0, ans2 = 0;
		for (int i = 0; i < n; i++) {
			gao.dijkstra(i);
			for (int j = 0; j < n; j++) {
				if (gao.d[j] == INF) ans1 += L;
				else ans1 += gao.d[j];
			}
			for (int j = 0; j < m; j++) {
				int u = e[j].u, v = e[j].v;
				if ((gao.p[v] != -1 && gao.edges[gao.p[v]].u == u) || ((gao.p[u] != -1) && gao.edges[gao.p[u]].u == v)) {
					gao2.init(n);
					for (int k = 0; k < m; k++) {
						if (j == k) continue;
						gao2.add_Edge(e[k].u, e[k].v, e[k].dist);
						gao2.add_Edge(e[k].v, e[k].u, e[k].dist);
					}
					gao2.dijkstra(i);
					for (int k = 0; k < n; k++) {
						if (gao2.d[k] == INF) c[j] += L;
						else c[j] += gao2.d[k];
					}
				} else {
					for (int k = 0; k < n; k++) {
						if (gao.d[k] == INF) c[j] += L;
						else c[j] += gao.d[k];
					}
				}
			}
		}
		for (int i = 0; i < m; i++)
			ans2 = max(ans2, c[i]);
		printf("%lld %lld\n", ans1, ans2);
	}
	return 0;
}

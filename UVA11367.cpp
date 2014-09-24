#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXNODE = 1005;
const int MAXEDGE = 20005;

typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge {
	int u, v;
	Type dist;
	Edge() {}
	Edge(int u, int v, Type dist) {
		this->u = u;
		this->v = v;
		this->dist = dist;
	}
};

struct HeapNode {
	Type d;
	int u, c;
	HeapNode() {}
	HeapNode(Type d, int u, int c) {
		this->d = d;
		this->u = u;
		this->c = c;
	}
	bool operator < (const HeapNode& c) const {
		return d > c.d;
	}
};

struct Dijkstra {
	int n, m;
	Edge edges[MAXEDGE];
	int price[MAXNODE];
	int first[MAXNODE];
	int next[MAXEDGE];
	bool done[MAXNODE][105];
	Type d[MAXNODE][105];

	void add_Edge(int u, int v, Type dist) {
		edges[m] = Edge(u, v, dist);
		next[m] = first[u];
		first[u] = m++;
	}

	int dijkstra(int s, int t, int c) {
		priority_queue<HeapNode> Q;
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= c; j++)
				d[i][j] = INF;
		d[s][0] = 0;
		memset(done, false, sizeof(done));
		Q.push(HeapNode(0, s, 0));
		while (!Q.empty()) {
			HeapNode x = Q.top(); Q.pop();
			int u = x.u, cc = x.c;
			if (u == t)
				return d[u][0];
			if (done[u][cc]) continue;
			done[u][cc] = true;
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (cc - e.dist >= 0) {
					int su = cc - e.dist;
					if (d[e.v][su] > d[u][cc]) {
						d[e.v][su] = d[u][cc];
						Q.push(HeapNode(d[e.v][su], e.v, su));
					}
				}
				if (cc + 1 <= c) {
					int su = cc + 1;
					if (d[u][su] > d[u][cc]) {
						d[u][su] = d[u][cc] + price[u];
						Q.push(HeapNode(d[u][su], u, su));
					}
				}
			}
		}
		return -1;
	}

	void init() {
		memset(first, -1, sizeof(first));
		for (int i = 0; i < n; i++)
			scanf("%d", &price[i]);
		int mm = m;
		m = 0;
		int u, v, d;
		for (int i = 0; i < mm; i++) {
			scanf("%d%d%d", &u, &v, &d);
			add_Edge(u, v, d);
			add_Edge(v, u, d);
		}
	}

	void solve() {
		init();
		int q;
		scanf("%d", &q);
		int s, t, c;
		while (q--) {
			scanf("%d%d%d", &c, &s, &t);
			int tmp = dijkstra(s, t, c);
			if (tmp == -1) printf("impossible\n");
			else printf("%d\n", tmp);
		}
	}
} gao;

int main() {
	while (~scanf("%d%d", &gao.n, &gao.m)) {
		gao.solve();
	}
	return 0;
}

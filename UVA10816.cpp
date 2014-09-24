#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int MAXNODE = 105;
const int MAXEDGE = 20005;

typedef double Type;
const Type INF = 0x3f3f3f3f;

struct Edge {
	int u, v;
	Type dist, d;
	Edge() {}
	Edge(int u, int v, Type dist, Type d = 0) {
		this->u = u;
		this->v = v;
		this->dist = dist;
		this->d = d;
	}
	void read() {
		scanf("%d%d%lf%lf", &u, &v, &d, &dist);
		u--; v--;
	}
};

struct HeapNode {
	Type d;
	int u;
	HeapNode() {}
	HeapNode(Type d, int u) {
		this->d = d;
		this->u = u;
	}
	bool operator < (const HeapNode& c) const {
		return d > c.d;
	}
};

int n, m, s, t;

struct Dijkstra {
	int n, m;
	Edge edges[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	bool done[MAXNODE];
	Type d[MAXNODE];
	int p[MAXNODE];

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}

	void add_Edge(int u, int v, Type dist) {
		edges[m] = Edge(u, v, dist);
		next[m] = first[u];
		first[u] = m++;
	}

	void add_Edge(Edge e) {
		edges[m] = e;
		next[m] = first[e.u];
		first[e.u] = m++;
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

	bool dijkstra(int s, int t) {
		priority_queue<HeapNode> Q;
		for (int i = 0; i < n; i++) d[i] = INF;
		d[s] = 0;
		p[s] = -1;
		memset(done, false, sizeof(done));
		Q.push(HeapNode(0, s));
		while (!Q.empty()) {
			HeapNode x = Q.top(); Q.pop();
			int u = x.u;
			if (u == t)
				return true;
			if (done[u]) continue;
			done[u] = true;
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (d[e.v] > d[u] + e.dist) {
					d[e.v] = d[u] + e.dist;
					p[e.v] = i;
					Q.push(HeapNode(d[e.v], e.v));
				}
			}
		}
		return false;
	}
} gao;

Edge e[MAXEDGE];

bool judge(double mid) {
	gao.init(n);
	for (int i = 0; i < m; i++) {
		if (e[i].d > mid) continue;
		gao.add_Edge(e[i]);
		gao.add_Edge(Edge(e[i].v, e[i].u, e[i].dist, e[i].d));
	}
	if (gao.dijkstra(s, t)) return true;
	return false;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		scanf("%d%d", &s, &t);
		s--; t--;
		for (int i = 0; i < m; i++)
			e[i].read();
		double l = 20, r = 50, mid;
		while (r - l > 1e-8) {
			mid = (l + r) / 2;
			if (judge(mid)) r = mid;
			else l = mid;
		}
		if (judge(r)) {
			gao.print(t); printf("\n");
			printf("%.1lf %.1lf\n", gao.d[t], mid);
		}
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f3f3f3f

const int MAXNODE = 505;

typedef long long Type;

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

struct Dijkstra {
	int n, m;
	vector<Edge> edges;
	vector<int> g[MAXNODE];
	bool done[MAXNODE];
	Type d[MAXNODE];
	int p[MAXNODE];

	void init(int tot) {
		n = tot;
		for (int i = 0; i < n; i++)
			g[i].clear();
		edges.clear();
	}

	void add_Edge(int u, int v, Type dist) {
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
} gao;

int main() {

	return 0;
}

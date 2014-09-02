#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef double Type;

const int MAXNODE = 55;

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

struct BellmanFrod {
	int n, m;
	vector<Edge> edges;
	vector<int> g[MAXNODE];
	bool inq[MAXNODE];
	Type d[MAXNODE];
	int p[MAXNODE];
	int cnt[MAXNODE];

	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) g[i].clear();
		edges.clear();
	}

	void add_Edge(int u, int v, Type dist) {
		edges.push_back(Edge(u, v, dist));
		m = edges.size();
		g[u].push_back(m - 1);
	}

	bool negativeCycle() {
		queue<int> Q;
		memset(inq, 0, sizeof(inq));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++) {
			d[i] = 0; inq[i] = true; Q.push(i);
		}

		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			inq[u] = false;
			for (int i = 0; i < g[u].size(); i++) {
				Edge& e = edges[g[u][i]];
				if (d[e.v] > d[u] + e.dist) {
					d[e.v] = d[u] + e.dist;
					p[e.v] = g[u][i];
					if (!inq[e.v]) {
						Q.push(e.v);
						inq[e.v] = true;
						if (++cnt[e.v] > n) return true;
					}
				}
			}
		}
		return false;
	}
} gao;

int main() {

	return 0;
}

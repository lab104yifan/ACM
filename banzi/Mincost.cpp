#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXNODE = 105;
const int MAXEDGE = 5005 * 4;
typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge {
	int u, v;
	Type cap, flow, cost;
	Edge() {}
	Edge(int u, int v, Type cap, Type flow, Type cost) {
		this->u = u;
		this->v = v;
		this->cap = cap;
		this->flow = flow;
		this->cost = cost;
	}
};

struct MCFC {
	int n, m, s, t;
	Edge edges[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	int inq[MAXNODE];
	Type d[MAXNODE];
	int p[MAXNODE];
	Type a[MAXNODE];

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}

	void add_Edge(int u, int v, Type cap, Type cost) {
		edges[m] = Edge(u, v, cap, 0, cost);
		next[m] = first[u];
		first[u] = m++;
		edges[m] = Edge(v, u, 0, 0, -cost);
		next[m] = first[v];
		first[v] = m++;
	}

	bool bellmanford(int s, int t, Type &flow, Type &cost) {

		for (int i = 0; i < n; i++) d[i] = INF;
		memset(inq, false, sizeof(inq));
		d[s] = 0; inq[s] = true; p[s] = s; a[s] = INF;
		queue<int> Q;
		Q.push(s);
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			inq[u] = false;
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (e.cap > e.flow && d[e.v] > d[u] + e.cost) {
					d[e.v] = d[u] + e.cost;
					p[e.v] = i;
					a[e.v] = min(a[u], e.cap - e.flow);
					if (!inq[e.v]) {Q.push(e.v); inq[e.v] = true;}
				}
			}
		}
		if (d[t] == INF) return false;
		flow += a[t];
		cost += d[t] * a[t];
		int u = t;
		while (u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]].u;
		}
		return true;
	}

	Type Mincost(int s, int t, Type D) {
		Type flow = 0, cost = 0;
		while (bellmanford(s, t, flow, cost));
		return cost;
	}
} gao;

int main() {

	return 0;
}

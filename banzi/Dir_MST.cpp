#include <cstdio>
#include <cstring>

const int MAXNODE = 1005;
const int MAXEDGE = 40005;

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

struct Directed_MST {
	int n, m;
	Edge edges[MAXEDGE];
	int vis[MAXNODE];
	int pre[MAXNODE];
	int id[MAXNODE];
	Type in[MAXNODE];

	void init(int n) {
		this->n = n;
		m = 0;
	}

	void add_Edge(int u, int v, Type dist) {
		edges[m++] = Edge(u, v, dist);
	}

	void add_Edge(Edge e) {
		edges[m++] = e;
	}

	Type dir_mst(int root) {
		Type ans = 0;
		while (true) {
			for (int i = 0; i < n; i++) in[i] = INF;
			for (int i = 0; i < m; i++) { //find min edge
				int u = edges[i].u;
				int v = edges[i].v;
				if (edges[i].dist < in[v] && u != v) {
					in[v] = edges[i].dist;
					pre[v] = u;
				}
			}

			for (int i = 0; i < n; i++) { //judge
				if (i == root) continue;
				if (in[i] == INF) return -1;
			}

			int cnt = 0;
			memset(id, -1, sizeof(id));
			memset(vis, -1, sizeof(vis));
			in[root] = 0;

			for (int i = 0; i < n; i++) { //find circle
				ans += in[i];
				int v = i;
				while (vis[v] != i && id[v] == -1 && v != root) {
					vis[v] = i;
					v = pre[v];
				}
				if (v != root && id[v] == -1) {
					for (int u = pre[v]; u != v; u = pre[u])
						id[u] = cnt;
					id[v] = cnt++;
				}
			}
			if (cnt == 0) break;
			for (int i = 0; i < n; i++)
				if (id[i] == -1) id[i] = cnt++;
			for (int i = 0; i < m; i++) {
				int v = edges[i].v;
				edges[i].u = id[edges[i].u];
				edges[i].v = id[edges[i].v];
				if (edges[i].u != edges[i].v)
					edges[i].dist -= in[v];
			}
			n = cnt;
			root = id[root];
		}
		return ans;
	}
} gao;

int main() {

	return 0;
}

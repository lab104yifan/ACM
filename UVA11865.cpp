#include <cstdio>
#include <cstring>

const int MAXNODE = 65;
const int MAXEDGE = 10005;

typedef long long Type;
const Type INF = 0x3f3f3f3f3f3f3f;

struct Edge {
	int u, v, kbps;
	Type dist;
	Edge() {}
	Edge(int u, int v, Type dist, int kbps = 0) {
		this->u = u;
		this->v = v;
		this->dist = dist;
		this->kbps = kbps;
	}

	void read() {
		scanf("%d%d%d%lld", &u, &v, &kbps, &dist);
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

typedef long long ll;

Edge e[MAXEDGE];
int t, n, m;
ll c;

bool judge(int mid) {
	gao.init(n);
	for (int i = 0; i < m; i++) {
		if (e[i].kbps < mid) continue;
		gao.add_Edge(e[i]);
	}
	ll tmp = gao.dir_mst(0);
	if (tmp == -1) return false;
	return tmp <= c;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%lld", &n, &m, &c);
		for (int i = 0; i < m; i++)
			e[i].read();
		int l = 0, r = 1000001;
		if (!judge(l)) printf("streaming not possible.\n");
		else {
			while (l < r) {
				int mid = (l + r) / 2;
				if (judge(mid)) l = mid + 1;
				else r = mid;
			}
			printf("%d kbps\n", l - 1);
		}
	}
	return 0;
}

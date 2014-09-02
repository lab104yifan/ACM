#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1005;

int n, m;

struct Edge {
	int u, v, id;
	int fan;
	bool iscut, used;
	Edge() {}
	Edge(int u, int v, int id, int fan) {
		this->u = u;
		this->v = v;
		this->id = id;
		this->fan = fan;
		used = false;
		iscut = false;
	}
};

int pre[N], low[N], dfs_clock;

vector<Edge> g[N];
vector<Edge> cut;

int dfs(int u, int fa) {
	int lowu = pre[u] = ++dfs_clock;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		int id = g[u][i].id;
		if (id == fa) continue;
		if (!pre[v]) {
			int lowv = dfs(v, id);
			lowu = min(lowu, lowv);
			if (lowv > pre[u]) {
				cut.push_back(g[u][i]);
				g[u][i].iscut = true;
				g[v][g[u][i].fan].iscut = true;
			}
		} else lowu = min(lowu, pre[v]);
	}
	return low[u] = lowu;
}

void find_cut(int n) {
	cut.clear();
	memset(pre, 0, sizeof(pre));
	dfs_clock = 0;
	for (int i = 0; i < n; i++) {
		if (!pre[i]) {
			dfs(i, 0);
		}
	}
}

int vis[N];

void print(int u) {
	vis[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		if (g[u][i].iscut) continue;
		if (g[u][i].used) continue;
		int v = g[u][i].v;
		g[u][i].used = true;
		g[v][g[u][i].fan].used = true;
		printf("%d %d\n", u + 1, v + 1);
		if (vis[v]) continue;
		print(v);
	}
}

int main() {
	int cas = 0;
	while (~scanf("%d%d", &n, &m) && n || m) {
		int u, v;
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &u, &v);
			u--; v--;
			g[u].push_back(Edge(u, v, i, g[v].size()));
			g[v].push_back(Edge(v, u, i, g[u].size() - 1));
		}
		find_cut(n);
		printf("%d\n\n", ++cas);
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++)
			if (!vis[i]) print(i);
		for (int i = 0; i < cut.size(); i++) {
			printf("%d %d\n", cut[i].u + 1, cut[i].v + 1);
			printf("%d %d\n", cut[i].v + 1, cut[i].u + 1);
		}
		printf("#\n");
	}
	return 0;
}

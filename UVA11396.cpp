#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

const int N = 305;

vector<int> g[N];

int n, color[N];

bool bipartite(int u) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (color[u] == color[v]) return false;
		if (!color[v]) {
			color[v] = 3 - color[u];
			if (!bipartite(v)) return false;
		}
	}
	return true;
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++) {
			g[i].clear();
			color[i] = 0;
		}
		int u, v;
		while (scanf("%d%d", &u, &v)) {
			if (u == 0 && v == 0) break;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		color[1] = 1;
		if (bipartite(1)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

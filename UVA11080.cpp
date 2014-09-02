#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 205;

int color[N];
vector<int> g[N];

int b, w;

int bipartite(int u) {
	if (color[u] == 1) b++;
	if (color[u] == 2) w++;
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

int t, n, m;

int solve() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (!color[i]) {
			color[i] = 1;
			b = w = 0;
			if (!bipartite(i)) return -1;
			ans += max(1, min(b, w));
		}
	}
	return ans;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) {
			g[i].clear();
			color[i] = 0;
		}
		int u, v;
		while (m--) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		printf("%d\n", solve());
	}
	return 0;
}

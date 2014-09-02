#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 105;

int n, m, c, a[N][N], vis[N];
vector<int> g[N];

int dfs(int u) {
	vis[u] = 1;
	int ans = 1;
	for (int i = 0; i < g[u].size(); i++) if (!vis[g[u][i]])
		ans += dfs(g[u][i]);
	return ans;
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &c) && n) {
		int u;
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++) {
				scanf("%d", &u);
				a[i][u] = j;
			}
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				int cnt = 0;
				for (int k = 1; k <= m; k++) {
					if (a[k][i] < a[k][j])
						cnt++;
					if (cnt > m / 2) break;
				}
				if (cnt > m / 2) g[i].push_back(j);
				else g[j].push_back(i);
			}
		}
		memset(vis, 0, sizeof(vis));
		printf("%s\n", dfs(c) == n ? "yes" : "no");
	}
	return 0;
}

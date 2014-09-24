#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100005;

int t, n, m, l, k, s[N];
bool vis[N], isch[N];
vector<int> g[N];

int dfs2(int u) {
	vis[u] = true;
	int ans = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (vis[v]) continue;
		ans += dfs2(v);
	}
	return ans;
}

void dfs(int u) {
	vis[u] = true;
	if (isch[u]) {
		isch[u] = false;
		return;
	}
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (vis[v]) continue;
		dfs(v);
	}
}

bool solve() {
	if (l < k) return false;
	if (dfs2(1) != n) return false;
	memset(vis, false, sizeof(vis));
	isch[s[0]] = false;
	for (int i = 0; i < l; i++) {
		if (isch[s[i]]) return false;
		dfs(s[i]);
	}
	return true;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; i++)
			g[i].clear();
		int tmp;
		memset(vis, false, sizeof(vis));
		memset(isch, false, sizeof(isch));
		for (int i = 0; i < k; i++) {
			scanf("%d", &tmp);
			isch[tmp] = true;
		}
		int u, v;
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		scanf("%d", &l);
		for (int i = 0; i < l; i++)
			scanf("%d", &s[i]);
		printf("%s\n", solve() ? "Yes" : "No");
	}
	return 0;
}

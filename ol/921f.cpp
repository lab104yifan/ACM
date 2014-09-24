#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 1005;

vector<int> g[N], scc[N], g2[N];
int pre[N], lowlink[N], sccno[N], dfs_clock, scc_cnt, val[N];
stack<int> S;

void dfs_scc(int u) {
	pre[u] = lowlink[u] = ++dfs_clock;
	S.push(u);
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!pre[v]) {
			dfs_scc(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		} else if (sccno[v] == -1)
			lowlink[u] = min(lowlink[u], pre[v]);
	}
	if (lowlink[u] == pre[u]) {
		int cnt = 0;
		while (1) {
			int x = S.top(); S.pop();
			sccno[x] = scc_cnt;
			cnt++;
			if (x == u) break;
		}
		val[scc_cnt] = cnt;
		scc_cnt++;
	}
}

void find_scc(int n) {
	dfs_clock = scc_cnt = 0;
	memset(sccno, -1, sizeof(sccno));
	memset(pre, 0, sizeof(pre));
	for (int i = 0; i < n; i++)
		if (!pre[i]) dfs_scc(i);
	for (int i = 0; i < scc_cnt; i++)
		g2[i].clear();
	for (int u = 0; u < n; u++) {
		for (int j = 0; j < g[u].size(); j++) {
			int v = g[u][j];
			int uu = sccno[u];
			int vv = sccno[v];
			if (uu != vv) g2[vv].push_back(uu);
		}
	}
}

int t, n, dp[N];
int vis[N];

int dfs(int u) {
	vis[u] = 1;
	int ans = val[u];
	for (int i = 0; i < g2[u].size(); i++) {
		int v = g2[u][i];
		if (vis[v]) continue;
		ans += dfs(v);
	}
	return ans;
}

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) g[i].clear();
		int num, v;
		for (int i = 0; i < n; i++) {
			scanf("%d", &num);
			memset(vis, 0, sizeof(vis));
			while (num--) {
				scanf("%d", &v); v--;
				if (v == i) continue;
				if (vis[v]) continue;
				vis[v] = 1;
				g[i].push_back(v);
			}
		}
		find_scc(n);
		memset(dp, 0, sizeof(dp));
		double ans = 0;
		for (int i = 0; i < scc_cnt; i++) {
			memset(vis, 0, sizeof(vis));
			dp[i] = dfs(i);
		}
		for (int i = 0; i < n; i++) {
			int u = sccno[i];
			ans += 1.0 / dp[u];
		}
		printf("Case #%d: %.5lf\n", ++cas, ans);
	}
	return 0;
}

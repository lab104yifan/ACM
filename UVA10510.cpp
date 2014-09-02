#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 20005;

vector<int> g[N];
int pre[N], lowlink[N], fa[N], dfs_clock, scc_cnt, cnt[N];
int flag;

bool find(int v, int u) {
	while (fa[u] != v) {
		cnt[u]++;
		if (cnt[u] > 1)
			return false;
		u = fa[u];
	}
	return true;
}

bool dfs_scc(int u) {
	pre[u] = lowlink[u] = ++dfs_clock;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!pre[v]) {
			fa[v] = u;
			if (!dfs_scc(v)) return false;
			lowlink[u] = min(lowlink[u], lowlink[v]);
		} else {
			lowlink[u] = min(lowlink[u], pre[v]);
			if (!find(v, u)) return false;
		}
	}
	if (lowlink[u] == pre[u]) {
		scc_cnt++;
		if (scc_cnt == 2) return false;
	}
	return true;
}

bool find_scc(int n) {
	dfs_clock = scc_cnt = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(pre, 0, sizeof(pre));
	for (int i = 0; i < n; i++) {
		if (!pre[i] && !dfs_scc(i))
			return false;
	}
	return true;
}

int T, n, m;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			g[i].clear();
		int u, v;
		while (m--) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
		}
		printf("%s\n", find_scc(n) ? "YES" : "NO");
	}
	return 0;
}

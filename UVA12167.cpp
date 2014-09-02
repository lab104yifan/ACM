#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 20005;

vector<int> g[N], scc[N];
int pre[N], lowlink[N], sccno[N], dfs_clock, scc_cnt;
stack<int> S;

void dfs_scc(int u) {
	pre[u] = lowlink[u] = ++dfs_clock;
	S.push(u);
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!pre[v]) {
			dfs_scc(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		} else if (!sccno[v])
			lowlink[u] = min(lowlink[u], pre[v]);
	}
	if (lowlink[u] == pre[u]) {
		scc_cnt++;
		while (1) {
			int x = S.top(); S.pop();
			sccno[x] = scc_cnt;
			if (x == u) break;
		}
	}
}

void find_scc(int n) {
	dfs_clock = scc_cnt = 0;
	memset(sccno, 0, sizeof(sccno));
	memset(pre, 0, sizeof(pre));
	for (int i = 0; i < n; i++)
		if (!pre[i]) dfs_scc(i);
}

int in[N], out[N];
int T, n, m;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) g[i].clear();
		int u, v;
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v); u--; v--;
			g[u].push_back(v);
		}
		find_scc(n);
		for (int i = 1; i <= scc_cnt; i++) in[i] = out[i] = 1;
		for (int u = 0; u < n; u++)
			for (int i = 0; i < g[u].size(); i++) {
				int v = g[u][i];
				if (sccno[u] != sccno[v]) in[sccno[v]] = out[sccno[u]] = 0;
			}
		int a = 0, b = 0;
		for (int i = 1; i <= scc_cnt; i++) {
			if (in[i]) a++;
			if (out[i]) b++;
		}
		int ans = max(a, b);
		if (scc_cnt == 1) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}

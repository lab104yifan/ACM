#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 100005;

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

int in[N];
int t, n, m, u[N], v[N];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u[i], &v[i]);
			u[i]--; v[i]--;
			g[u[i]].push_back(v[i]);
		}
		find_scc(n);
		memset(in, 0, sizeof(in));
		for (int i = 0; i < m; i++) {
			if (sccno[u[i]] != sccno[v[i]])
				in[sccno[v[i]]]++;
		}
		int ans = 0;
		for (int i = 1; i <= scc_cnt; i++)
			if (in[i] == 0) ans++;
		printf("%d\n", ans);
	}
	return 0;
}

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
	return 0;
}

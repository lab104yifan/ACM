#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 55;
const int M = 10005;

int t, n, m, d;
double dp[N][M];
vector<int> g[N];

double solve(int u) {
	double ans = 0;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 0; i <= d; i++) {
		for (int j = 0; j <= n; j++) {
			if (u == j) continue;
			double p = 1.0 / g[j].size();
			for (int k = 0; k < g[j].size(); k++) {
				dp[g[j][k]][i + 1] += dp[j][i] * p;
			}
		}
		ans += dp[u][i + 1];
	}
	return 1.0 - ans;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &d);
		for (int i = 0; i <= n; i++)
			g[i].clear();
		int u, v;
		while (m--) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		for (int i = 1; i <= n; i++)
			g[0].push_back(i);
		for (int i = 1; i <= n; i++)
			printf("%.10lf\n", solve(i));
	}
	return 0;
}

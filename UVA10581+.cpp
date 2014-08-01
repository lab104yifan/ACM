#include <cstdio>
#include <cstring>

typedef long long LL;
int t, M, n, vis[15][225][225];
LL k, dp[15][225][225];

LL DP(int now, int tail, int m) {
    LL &ans = dp[now][tail][m];
    if (vis[now][tail][m]) return ans;
    vis[now][tail][m] = 1;
    ans = 0;
    if (now == n) return ans = 1;
    if (now == n - 1) {
	if (m >= tail)
	    return ans = DP(now + 1, m, 0);
	return ans = 0;
    }
    for (int i = tail; i <= m - (n - now - 1); i++)
	ans += DP(now + 1, i, m - i);
    return ans;
}

void solve(LL k) {
    int v = 1;
    for (int i = 1; i < n; i++) {
	for (int j = v; j <= M - (n - i); j++) {
	    if (k > dp[i][j][M - j]) k -= dp[i][j][M - j];
	    else {
		M -= j;
		v = j;
		printf("%d\n", j);
		break;
	    }
	}
    }
    printf("%d\n", M);
}

int main() {
    scanf("%d", &t);
    while (t--) {
	memset(vis, 0, sizeof(vis));
	scanf("%d%d%lld", &M, &n, &k);
	DP(0, 1, M);
	solve(k);
    }
    return 0;
}

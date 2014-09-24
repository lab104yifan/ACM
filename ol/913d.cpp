#include <cstdio>
#include <cstring>

const int MOD = 1000000007;

const int N = 2005;

int t, n, dp[N], T[N];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &T[i]);
			sum += T[i];
		}
		sum /= 2;
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int k = sum; k >= 0; k--) {
				for (int j = 1; j <= T[i]; j++) {
					if (k - j < 0) break;
					dp[k] = (dp[k] + dp[k - j]) % MOD;
				}
			}
		}
		printf("%d\n", dp[sum]);
	}
	return 0;
}

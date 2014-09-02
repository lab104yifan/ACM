#include <cstdio>
#include <cstring>

const int N = 10005;

double dp[N];
int n, m;

int main() {
	while (~scanf("%d%d", &m, &n)) {
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = i - 1; j > i - 1 - m && j >= 0; j--)
				dp[i] += dp[j] * (1.0 / m);
		}
		printf("%.5lf\n", dp[n]);
	}
	return 0;
}

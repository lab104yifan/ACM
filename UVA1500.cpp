#include <cstdio>
#include <cstring>

const int N = 1005;

int t, n, a, sum, cnt, dp[55][55 * N];

int solve(int cnt, int sum) {
    if (sum == 1) {
	cnt++;
	sum--;
    }
    if (dp[cnt][sum] != -1) return dp[cnt][sum];
    int &ans = dp[cnt][sum];
    ans = 0;
    if (cnt == 0 && sum == 0) return ans;
    if (cnt >= 1 && !solve(cnt - 1, sum)) ans = 1;
    if (sum >= 1 && !solve(cnt, sum - 1)) ans = 1;
    if (cnt >= 2 && sum > 0 && !solve(cnt - 2, sum + 3)) ans = 1;
    if (cnt >= 2 && sum == 0 && !solve(cnt - 2, sum + 2)) ans = 1;
    if (cnt >= 1 && sum > 0 && !solve(cnt - 1, sum + 1)) ans = 1;
    return ans;
}

int main() {
    int cas = 0;
    memset(dp, -1, sizeof(dp));
    scanf("%d", &t);
    while (t--) {
	cnt = sum = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
	    scanf("%d", &a);
	    if (a == 1) cnt++;
	    else sum += a;
	}
	if (cnt != n)
	    sum += n - cnt - 1;
	printf("Case #%d: %s\n", ++cas, solve(cnt, sum) ? "Alice" : "Bob");
    }
    return 0;
}

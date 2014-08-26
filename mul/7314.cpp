#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = (1<<20) + 5;
const ll MOD = 1000000007;
int t, n, k;
ll l, dp[N];

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d%lld", &n, &k, &l);
	int s = (1<<k);
	if (l > k) {
	    ll yu = l - k;
	    l = k;
	}
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	while (n--) {
	    for (int i = s - 1; i >= 0; i--) {
		if (dp[i] == 0) continue;
		ll tmp = yu * dp[i] % MOD;
		ll now = dp[i];
		for (int j = 1; j <= l; j++) {
		    int next = i|((i<<j)&(s - 1)|(1<<(j - 1)));
		    dp[next] = (dp[next] + now) % MOD;
		}
		dp[i] = (dp[i] + tmp) % MOD;
	    }
	}
	ll ans = 0;
	for (int i = 0; i < s; i++) {
	    if (i&(1<<(k - 1))) {
		ans = (ans + dp[i]) % MOD;
	    }
	}
	printf("%lld\n", ans);
    }
    return 0;
}

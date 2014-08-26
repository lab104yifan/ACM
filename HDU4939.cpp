#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1505;

typedef long long ll;
int T;
ll n, x, y, z, t;
ll dp[N][N];

ll solve() {
    ll ans = n * x * t;
    dp[0][0] = 0;
    for (ll i = 1; i <= n; i++) {
	for (ll j = 0; j <= i; j++) {
	    dp[i][j] = 0;
	    if (j != i)
		dp[i][j] = max(dp[i][j], dp[i - 1][j] + y * j * (t + (i - j - 1) * z));
	    if (j)
		dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + y * (j - 1) * (t + (i - j) * z));
	    ans = max(ans, dp[i][j] + (t + (i - j) * z) * (n - i) * (x + y * j));
	}
    }
    return ans;
}

int main() {
    int cas = 0;
    scanf("%d", &T);
    while (T--) {
	scanf("%I64d%I64d%I64d%I64d%I64d", &n, &x, &y, &z, &t);
	printf("Case #%d: %I64d\n", ++cas, solve());
    }
    return 0;
}

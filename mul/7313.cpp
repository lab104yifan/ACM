#include <cstdio>
#include <cstring>

typedef __int64 ll;
const int N = 1024;
const int M = 2048;

const int MOD = 1000000007;

int t, n, a[N], l[N][M], r[N][N], ls[N][M], rs[N][N];

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	    scanf("%d", &a[i]);
	memset(l, 0, sizeof(l));
	memset(ls, 0, sizeof(ls));
	l[1][a[1]] = ls[1][a[1]] = 1;
	for (int i = 2; i <= n; i++) {
	    for (int j = 0; j < M; j++)
		l[i][a[i]^j] = (l[i][a[i]^j] + ls[i - 1][j]) % MOD;
	    l[i][a[i]] = (l[i][a[i]] + 1) % MOD;
	    for (int j = 0; j < M; j++)
		ls[i][j] = (ls[i - 1][j] + l[i][j]) % MOD;
	}
	memset(r, 0, sizeof(r));
	memset(rs, 0, sizeof(rs));
	r[n][a[n]] = rs[n][a[n]] = 1;
	for (int i = n - 1; i >= 1; i--) {
	    for (int j = 0; j < N; j++)
		r[i][a[i]&j] = (r[i][a[i]&j] + rs[i + 1][j]) % MOD;
	    r[i][a[i]] = (r[i][a[i]] + 1) % MOD;
	    for (int j = 0; j < N; j++)
		rs[i][j] = (rs[i + 1][j] + r[i][j]) % MOD;
	}
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	    for (int j = 0; j < N; j++) {
		ans += ((ll)ls[i][j] * r[i + 1][j] % MOD);
		ans %= MOD;
	    }
	printf("%I64d\n", ans);
    }
    return 0;
}

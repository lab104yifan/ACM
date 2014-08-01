#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
const long long MOD = 1000000007;

int t;
ll n, k, l;

int bitcount(int x) {
    return x == 0 ? 0 : bitcount(x / 2) + (x&1);
}

long long pow_mod(long long x, long long k, long long mod) {
    long long ans = 1;
    while (k) {
	ans = ans * x % mod;
	x = x * x % mod;
	k /= 2;
    }
    return ans;
}

long long inv(long long a, long long b) {
    return pow_mod(a, b - 2, b);
}

ll C(long long n, long long m) {
    long long ans = 1;
    for (ll i = 0; i < m; i++)
	ans = ans * (n - i) % MOD * inv(i + 1, MOD) % MOD;
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	long long ans = 0;
	scanf("%lld%lld%lld", &n, &k, &l);
	for (int i = 0; i < (1<<n); i++) {
	    ll s = k;
	    for (int j = 0; j < n; j++) {
		if (i&(1<<j)) {
		    s -= l + 1;
		    if (s < 0) break;
		}
		if (s < 0) continue;
		if (bitcount(i)&1) ans = ((ans - C(s + n - 1, n - 1)) % MOD + MOD) % MOD;
		else ans = (ans + C(s + n - 1, n - 1)) % MOD;
	    }
	}
	printf("%lld\n", (ans + MOD) % MOD);
    }
    return 0;
}

#include <cstdio>
#include <cstring>

const long long N = 10000005;
const long long mod = 100000007;

long long ispri[N], fac[N], phi[N];

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {x = 1; y = 0; return a;}
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long inv(long long a, long long n) {
    long long x, y;
    exgcd(a, n, x, y);
    return (x + n) % n;
}

void get_table() {
    fac[0] = fac[1] = 1; phi[0] = phi[1] = 1;
    for (long long i = 2; i < N; i++) {
	fac[i] = (fac[i - 1] * i) % mod;
	if (ispri[i]) {
	    phi[i] = phi[i - 1];
	    continue;
	}
	phi[i] = phi[i - 1] * (i - 1) % mod * inv(i, mod) % mod;
	for (long long j = i * i; j < N; j += i)
	    ispri[j] = 1;
    }
}

int n, m;

int main() {
    get_table();
    while (~scanf("%d%d", &n, &m) && n) {
	printf("%lld\n", ((fac[n] * phi[m] - 1) % mod + mod) % mod);
    }
    return 0;
}

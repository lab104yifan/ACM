#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int t;
long long n, m, p;

long long pow(long long n, long long k) {
    if (k == 0) return 1;
    if (k == 1) return n;
    long long ans = pow(n * n % p, k>>1);
    if (k&1) ans = ans * n % p;
    return ans;
}

long long C(long long n, long long m) {
    if (m > n) return 0;
    m = min(m, n - m);
    long long zi = 1, mu = 1;
    for (long long i = 0; i < m; i++) {
	zi = zi * (n - i) % p;
	mu = mu * (i + 1) % p;
    }
    return zi * pow(mu, p - 2) % p;
}

long long Lucas(long long n, long long m, long long p) {
    if (m == 0) return 1;
    return C(n % p, m % p) * Lucas(n / p, m / p, p) % p;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%lld%lld%lld", &n, &m, &p);
	printf("%lld\n", Lucas(n + m, m, p));
    }
    return 0;
}

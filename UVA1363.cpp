#include <stdio.h>
#include <string.h>
#include <math.h>

long long n, k;

long long solve() {
    long long ans = 0;
    if (n > k) ans += (n - k) * k;
    long long a = (long long )sqrt(k), b = k / a;
    for (long long i = a; i > 1; i--) {
	long long a0 = k / i, an = k / (i - 1);
	if (a0 > n) break;
	if (an > n) an = n;
	ans += (k % an + k % (a0 + 1)) * (an - a0) / 2;
    }
    for (int i = 1; i <= n && i <= b; i++) ans += k % i;
    return ans;
}

int main() {
    while (~scanf("%lld%lld", &n, &k)) {
	printf("%lld\n", solve());
    }
    return 0;
}

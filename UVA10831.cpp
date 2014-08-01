#include <stdio.h>
#include <string.h>

long long a, p;

long long pow_mod(long long x, long long k, long long mod) {
    long long ans = 1;
    while (k) {
	if (k&1) ans = ans * x % mod;
	x = x * x % mod;
	k >>= 1;
    }
    return ans;
}

int lederang(long long a, long long p) {
    a %= p;
    if (a == 0) return 0;
    if (pow_mod(a, (p - 1) / 2, p) == 1) return 1;
    return -1;
}

int main() {
    while (~scanf("%lld%lld", &a, &p) && a != -1) {
	if (lederang(a, p) < 0) printf("No\n");
	else printf("Yes\n");
    }
    return 0;
}

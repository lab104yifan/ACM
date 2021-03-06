#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;

long long l, u, v, t;

long long gcd(long long a, long long b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int main() {
    while (~scanf("%lld%lld%lld%lld", &l, &u, &v, &t) && l) {
	if (u == 0 && v == 0) {
	    printf("0\n");
	    continue;
	}
	if (u < v) swap(u, v);
	long long ans = 0;
	ans += ((u + v) * t + l) / (2 * l);
	ans += ((u - v) * t + l) / (2 * l);
	long long d = gcd(u, v);
	if ((u - v) / d % 2)
	    ans -= (d * t + l) / (2 * l);
	printf("%lld\n", ans);
    }
    return 0;
}

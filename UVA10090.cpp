#include <stdio.h>
#include <string.h>
#include <math.h>

long long extend_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {x = 1; y = 0; return a;}
    long long d = extend_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long n, c1, c2, n1, n2;

int main() {
    while (~scanf("%lld", &n) && n) {
	scanf("%lld%lld%lld%lld", &c1, &n1, &c2, &n2);
	long long x, y;
	long long d = extend_gcd(n1, n2, x, y);
	long long downk = ceil(1.0 * -n * x / n2);
	long long upk = floor(1.0 * n * y / n1);
	if (downk > upk || n % d) {
	    printf("failed\n");
	    continue;
	}
	if (c1 * n2 < c2 * n1) {
	    x = n * x / d + n2 / d * upk;
	    y = n * y / d - n1 / d * upk;
	}
	else {
	    x = n * x / d + n2 / d * downk;
	    y = n * y / d - n1 / d * downk;
	}
	printf("%lld %lld\n", x, y);
    }
    return 0;
}

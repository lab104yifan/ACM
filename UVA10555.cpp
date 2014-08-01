#include <stdio.h>
#include <string.h>

char str[105];
const long long INF = 0x3f3f3f3f3f3f3f;

long long gcd(long long a, long long b) {
    if (!b) return a;
    return gcd(b, a % b);
}

void solve() {
    int len = strlen(str) - 5;
    for (int i = 0; i < len; i++)
	str[i] = str[i + 2];
    long long n1 = 0, m1 = 1;
    long long anszi, ansmu = INF;
    for (int i = 0; i < len; i++) {
	n1 = n1 * 10 + str[i] - '0';
	m1 *= 10;
    }
    for (int i = 0; i < len; i++) {
	int n2 = 0, m2 = 1;
	for (int j = 0; j < i; j++) {
	    n2 = n2 * 10 + str[j] - '0';
	    m2 *= 10;
	}
	long long zi = n1 - n2, mu = m1 - m2;
	long long k = gcd(zi, mu);
	zi /= k; mu /= k;
	if (mu < ansmu) {
	    anszi = zi;
	    ansmu = mu;
	}
    }
    printf("%lld/%lld\n", anszi, ansmu);
}

int main() {
    while (~scanf("%s", str) && strcmp(str, "0") != 0) {
	solve();
    }
    return 0;
}

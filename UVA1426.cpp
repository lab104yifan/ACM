#include <stdio.h>
#include <string.h>
#include <math.h>
#include <set>
using namespace std;

long long X, N, R;
set<long long> ans;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {x = 1; y = 0; return a;}
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

void mod_line(long long a, long long b, long long n) {
    long long x, y;
    long long d = exgcd(a, n, x, y);
    if (b % d) return;
    x = x * (b / d);
    x = (x % (n / d) + (n / d)) % (n / d);
    long long a0 = x * a - b / 2;
    long long k = a * n / d;
    for (long long tmp = a0; tmp < N; tmp += k) {
	if (tmp >= 0) ans.insert(tmp);
    }
}

int main() {
    int cas = 0;
    while (~scanf("%lld%lld%lld", &X, &N, &R) && N) {
	ans.clear();
	long long m = (long long)sqrt(N);
	for (long long i = 1; i <= m; i++) {
	    if (N % i) continue;
	    mod_line(i, 2 * R, N / i);
	    mod_line(N / i, 2 * R, i);
	}
	printf("Case %d:", ++cas);
	for (set<long long>::iterator it = ans.begin(); it != ans.end(); it++)
	    printf(" %lld", *it);
	printf("\n");
    }
    return 0;
}

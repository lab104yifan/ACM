#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const long long INF = 10000000000000000LL;
int t;
long long a, b, c;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {x = 1; y = 0; return a;}
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

long long solve() {
    long long x, y, d;
    d = exgcd(a, b, x, y);
    if (c % d) return 0;
    long long down = -INF, up = INF;
    if (b / d > 0)
	down = max(down, (long long)ceil((-x * 1.0 * c) / b));
    else
	up = min(up, (long long)floor((-x * 1.0 * c) / b));
    if (a / d > 0)
	up = min(up, (long long )floor((y * 1.0 * c) / a));
    else
	down = max(down, (long long)ceil((y * 1.0 * c) / a));
    if (up == INF || down == -INF) return -1;
    if (down <= up) return up - down + 1;
    return 0;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%lld%lld%lld", &a, &b, &c);
	long long ans = solve();
	if (ans == 0) printf("Impossible\n");
	else if (ans < 0) printf("Infinitely many solutions\n");
	else printf("%lld\n", ans);
    }
    return 0;
}

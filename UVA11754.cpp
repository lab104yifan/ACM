#include <stdio.h>
#include <string.h>
#include <math.h>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {x = 1; y = 0; return a;}
    long long d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

long long inv(long long a, long long n) {
    long long x, y;
    exgcd(a, n, x, y);
    return (x + n) % n;
}

long long pow_mod(long long x, long long k, long long n) {
    if (k == 0) return 1;
    long long ans = pow_mod(x * x % n, k>>1, n);
    if (k&1)
	ans = ans * x % n;
    return ans;
}

long long log_mod(long long a, long long b, long long n) {
    long long m = (long long)sqrt(n + 0.5), v, e = 1, i;
    v = inv(pow_mod(a, m, n), n);
    map<long long, long long> x;
    x[1] = 0;
    for (long long i = 1; i < m; i++) {
	e = e * a % n;
	if (!x.count(e)) x[e] = i;
    }
    for (long long i = 0; i < m; i++) {
	if (x.count(b)) return i * m + x[b];
	b = b * v % n;
    }
    return -1;
}

const long long MOD = 100000007;
long long t, n, k, b, r, Max, x[505], y[505];
typedef pair<long long, long long> pii;

set<pii> beats;

long long cal() {
    long long ans = 0;
    for (long long i = 0; i < b; i++) {
	if (x[i] != Max && !beats.count(make_pair(x[i] + 1, y[i])))
	    ans++;
    }
    ans += n;
    for (long long i = 0; i < b; i++) if (x[i] == 1) ans--;
    return pow_mod(k, ans,  MOD) * pow_mod(k - 1, Max * n - b - ans, MOD) % MOD;
}

long long solve() {
    long long m = cal();
    if (m == r) return Max;
    long long tmp = n;
    for (long long i = 0; i < b; i++)
	if (x[i] == Max) tmp--;
    long long ans = pow_mod(k - 1, tmp, MOD) * pow_mod(k, n - tmp, MOD) % MOD;
    m = m * ans % MOD;
    if (m == r) return Max + 1;
    return log_mod(pow_mod(k - 1, n, MOD), r * inv(m, MOD) % MOD, MOD) + Max + 1;
}

int main() {
    long long cas = 0;
    scanf("%lld", &t);
    while (t--) {
	beats.clear();
	Max = 1;
	scanf("%lld%lld%lld%lld", &n, &k, &b, &r);
	for (long long i = 0; i < b; i++) {
	    scanf("%lld%lld", &x[i], &y[i]);
	    beats.insert(make_pair(x[i], y[i]));
	    Max = max(Max, x[i]);
	}
	printf("Case %lld: %lld\n", ++cas, solve());
    }
    return 0;
}

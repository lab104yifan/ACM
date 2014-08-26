#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

int T;
ll n, x, y, z, t;

ll cal(ll a, ll b, ll c) {
    ll aa = y * (a * (a - 1) / 2) * t;
    ll bb = a * y * (t * b + (b * (b - 1) / 2) * z);
    ll cc = (t + b * z) * (x + a * y) * c;
    return aa + bb + cc;
}

int main() {
    scanf("%d", &T);
    int cas = 0;
    while (T--) {
	ll ans = 0;
	scanf("%lld%lld%lld%lld%lld", &n, &x, &y, &z, &t);
	for (ll i = 0; i <= n; i++) {
	    for (ll j = 0; j <= n - i; j++) {
		ll k = n - i - j;
		ans = max(ans, cal(i, j, k));
	    }
	}
	printf("Case #%d: %lld\n", ++cas, ans);
    }
    return 0;
}

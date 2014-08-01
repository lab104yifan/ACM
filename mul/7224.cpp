#include <cstdio>
#include <cstring>

typedef long long ll;
const ll MOD = 1000000009;
const int N = 100005;
int n, m, num;
ll fac[N];

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {x = 1; y = 0; return a;}
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll inv(ll a, ll n) {
    ll x, y;
    exgcd(a, n, x, y);
    return (x + n) % n;
}

ll C(int n, int m) {
    return fac[n] * inv(fac[m] * fac[n - m] % MOD, MOD) % MOD;
}

int main() {
    fac[0] = 1;
    for (ll i = 1; i < N; i++)
	fac[i] = fac[i - 1] * i % MOD;
    while (~scanf("%d%d", &n, &m)) {
	scanf("%d", &num);
	int up = num;
	int down = num;
	for (int i = 1; i < n; i++) {
	    scanf("%d", &num);
	    int up2 = m - down;
	    int down2 = m - up;
	    if (num >= down && num <= up)
		down = ((down&1)^(num&1));
	    else if (num < down) down = down - num;
	    else down = num - up;

	    if (num >= down2 && num <= up2) {
		up = m - ((up2&1)^(num&1));
	    }
	    else if (num < down2) {
		up = m - (down2 - num);
	    }
	    else up = m - (num - up2);
	}
	ll ans = 0;
	for (int i = down; i <= up; i += 2) {
	    ans = (ans + C(m, i)) % MOD;
	}
	printf("%lld\n", ans);
    }
    return 0;
}

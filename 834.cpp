#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

typedef long long ll;

const int N = 1000005;
ll n, prime[N];
int vis[N], pn;

ll mul(ll a, ll b, ll mod) {
    ll ret = 0;
    while (b > 0) {
	if (b&1) ret = (ret + a) % mod;
	b >>= 1;
	a = (a<<1) % mod;
    }
    return ret;
}

ll pow_mod(ll x, ll k, ll mod) {
    ll ans = 1;
    while (k) {
	if (k&1) ans = mul(ans, x, mod);
	x = mul(x, x, mod);
	k >>= 1;
    }
    return ans;
}

bool mlrb (ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 0; i < 20; i++) {
	ll a = rand() % (n - 1) + 1;
	if (pow_mod(a, n - 1, n) != 1)
	    return false;
    }
    return true;
}

void get_table() {
    pn = 0;
    for (ll i = 2; i < N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (ll j = i * i; j < N; j += i)
	    vis[j] = 1;
    }
}

bool check(ll n) {
    for (int i = 1; i < pn; i++) {
	if (n % prime[i] == 0) {
	    ll tmp = n;
	    while (tmp % prime[i] == 0)
		tmp /= prime[i];
	    if (tmp == 1) 
		return true;
	    else
		return false;
	}
    }
    if (mlrb(n)) return true;
    ll m = (ll)sqrt(n * 1.0);
    if (m * m == n) return true;
    return false;
}

bool judge(ll n) {
    if (n == 1 || n == 2 || n == 4) return true;
    if (n % 4 == 0) return false;
    if (n % 2 && check(n)) return true;
    if (n % 2 == 0 && check(n / 2)) return true;
    return false;
}

int main() {
    get_table();
    while (~scanf("%I64d", &n) && n != -1) {
	if (judge(n)) printf("%I64d\n", n - 1);
	else printf("1\n");
    }
    return 0;
}

#include <cstdio>
#include <cstring>

typedef long long ll;
int t;
ll n, ans, mi[30], save[30];

bool check(ll n) {
    while (n) {
	if (n % 10 < 3 || n % 10 > 6) return false;
	n /= 10;
    }
    return true;
}

ll cal(ll base, int d) {
    ll now = 1;
    ll ans = 0;
    for (int i = 0; i < d; i++) {
	ans += now * save[i];
	if (ans > n) return -1;
	now *= base;
    }
    return ans;
}

bool jud(ll base, int d) {
    if (base > 6) return true;
    for (int i = 0; i < d; i++)
	if (base <= save[i]) return false;
    return true;
}

void dfs(int d, ll sum) {
    ll l = 4, r = n - 1;
    while (l < r) {
	ll mid = (l + r) / 2;
	if (cal(mid, d) != -1) l = mid + 1;
	else r = mid;
    }
    if ((cal(l - 1, d) == n && jud(l - 1, d)) || (cal(l, d) == n && jud(l, d))) ans++;
    for (int i = 3; i <= 6; i++) {
	save[d] = i;
	if (sum + mi[d] * i <= n)
	    dfs(d + 1, sum + mi[d] * i);
    }
}

ll solve() {
    if (check(n)) return -1;
    ans = 0;
    dfs(0, 0);
    return ans;
}

int main() {
    mi[0] = 1;
    for (int i = 1; i < 30; i++)
	mi[i] = mi[i - 1] * 4;
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%lld", &n);
	printf("Case #%d: %lld\n", ++cas, solve());
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll N = 1e6 + 5;

int t, vis[N], pn = 0, cnt[N], fn;
ll n, prime[N], fra[N];
set<ll> ans;

void getFra(ll n) {
    fn = 0;
    for (int i = 0; i < pn && n >= prime[i]; i++) {
	if (n % prime[i] == 0) {
	    fra[fn] = prime[i];
	    cnt[fn] = 0;
	    while (n % prime[i] == 0) {
		n /= prime[i];
		cnt[fn]++;
	    }
	    fn++;
	}
    }
    if (n != 1) {
	fra[fn] = n;
	cnt[fn++] = 1;
    }
}

bool check(ll b) {
    ll tmp = n;
    while (tmp) {
	if (tmp % b < 3 || tmp % b > 6)
	    return false;
	tmp /= b;
    }
    return true;
}

void dfs(int now, ll sum) {
    if (now == fn) {
	if (check(sum))
	    ans.insert(sum);
	return;
    }
    ll tmp = 1;
    for (int i = 0; i <= cnt[now]; i++) {
	dfs(now + 1, sum * tmp);
	tmp *= fra[now];
    }
}

void solve(ll n, ll bas) {
    getFra(n);
    dfs(0, 1);
}

bool judge(ll n) {
    if (n == 3 || n == 4 || n == 5|| n == 6)
	return true;
    return false;
}

int main() {
    for (ll i = 2; i < N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (ll j = i * i; j < N; j += i)
	    vis[j] = 1;
    }
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%I64d", &n);
	if (judge(n)) {
	    printf("Case #%d: -1\n", ++cas);
	    continue;
	}
	ans.clear();
	for (ll i = 3; i <= 6; i++)
	    solve(n - i, i);
	int out = ans.size();
	printf("Case #%d: %d\n", ++cas, out);
    }
    return 0;
}

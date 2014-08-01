#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 10005;
int vis[N], prime[N], pn, n, f[N], fn, ans;

void get_prime(int n) {
    pn = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= n; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (int j = i * i; j < N; j += i)
	    vis[j] = 1;
    }
}

void build(int n) {
    fn = 0;
    ans = 200000000;
    for (int i = 0; i < pn && (prime[i] - 1) * (prime[i] - 1) <= n; i++) {
	if (n % (prime[i] - 1)) continue;
	f[fn++] = prime[i];
    }
}

bool judge(int sum) {
    for (int i = 0; i < pn && prime[i] * prime[i] <= sum; i++)
	if (sum % prime[i] == 0) return false;
    for (int i = 0; i < fn; i++) {
	if (vis[i] && f[i] == sum) return false;
    }
    return true;
}

void dfs(int now, int sum, int tot) {
    if (now == fn) {
	if (sum == 1) ans= min(ans, tot);
	else if (judge(sum + 1)) {
		tot *= (sum + 1);
	    ans = min(ans, tot);
	}
	return;
    }
    dfs(now + 1, sum, tot);
    if (sum % (f[now] - 1)) return;
    vis[now] = 1;
    sum /= (f[now] - 1);
    tot *= f[now];
    dfs(now + 1, sum, tot);
    while (sum % f[now] == 0) {
	sum /= f[now];
	tot *= f[now];
	dfs(now + 1, sum, tot);
    }
    vis[now] = 0;
}

int main() {
    get_prime(10000);
    int cas = 0;
    while (~scanf("%d", &n) && n) { 
	build(n);
	memset(vis, 0, sizeof(vis));
	dfs(0, n, 1);
	printf("Case %d: %d %d\n", ++cas, n, ans);
    }
    return 0;
}

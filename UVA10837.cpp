#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 20005;
const long long MAXN = 200000000;
const long long M = (int)sqrt(MAXN);
long long prime[N], f[N], n, ans;
int vis[N], pn, fn;

void prime_table() {
    pn = 0; vis[1] = 1; vis[0] = 1;
    for (long long i = 2; i <= M; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (long long j = i * i; j <= M; j += i)
	    vis[j] = 1;
    }
}

void frc(long long n) {
    fn = 0;
    for (int i = 0; i < pn && (prime[i] - 1) * (prime[i] - 1) <= n; i++) {
	if (n % (prime[i] - 1)) continue;
	f[fn++] = prime[i];
    }
}

long long cal(long long sum) {
    long long ans = n / sum;
    for (int i = 0; i < fn; i++) {
	if (vis[i] == 0) continue;
	ans *= f[i];
    }
    return ans;
}

void dfs(int now, long long sum) {
    if (sum * (f[now] - 1) > n) return;
    if (now == fn) {
	ans = min(ans, cal(sum));
	return;
    }
    vis[now] = 1;
    dfs(now + 1, sum * (f[now] - 1));
    vis[now] = 0;
    dfs(now + 1, sum);
}

int main() {
    int cas = 0;
    prime_table();
    while (~scanf("%lld", &n) && n) {
	ans = MAXN;
	memset(vis, 0, sizeof(vis));
	frc(n);
	for (int i = 0; i < fn; i++)
	    printf("%lld ", f[i]);
	dfs(0, 1);
	printf("Case %d: %lld %lld\n", ++cas, n, ans);
    }
    return 0;
}

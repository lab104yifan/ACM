#include <cstdio>
#include <cstring>

const int N = 100005;
int c, n, a[N], sum[N], vis[N];

void solve() {
    memset(vis, -1, sizeof(vis));
    vis[0] = 0;
    for (int i = 1; i <= n; i++) {
	sum[i] = (sum[i - 1] + a[i]) % c;
	if (vis[sum[i]] != -1) {
	    for (int j = vis[sum[i]] + 1; j < i; j++)
		printf("%d ", j);
	    printf("%d\n", i);
	    return;
	}
	vis[sum[i]] = i;
    }
}

int main() {
    while (~scanf("%d%d", &c, &n) && c + n) {
	for (int i = 1; i <= n; i++)
	    scanf("%d", &a[i]);
	solve();
    }
    return 0;
}

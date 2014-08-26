#include <cstdio>
#include <cstring>

int t, n, vis[10005];

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	int l, r;
	for (int i = 0; i < n; i++) {
	    scanf("%d%d", &l, &r);
	    vis[l] = r;
	}
	int ans = 0;
	for (int i = 1; i <= 10000; i++) {
	    if (vis[i]) {
		int cnt = 0;
		int now = vis[i];
		vis[i] = 0;
		while (vis[now]) {
		    cnt++;
		    int tmp = vis[now];
		    vis[now] = 0;
		    now = tmp;
		}
		ans += cnt;
	    }
	}
	printf("%d\n", ans);
    }
    return 0;
}

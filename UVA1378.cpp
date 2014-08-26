#include <cstdio>
#include <cstring>

const int N = 30;

int n, a[N], sg[N], vis[N * N];

void getsg() {
    for (int i = 0; i < 23; i++) {
	memset(vis, 0, sizeof(vis));
	for (int j = 0; j < i; j++) {
	    for (int k = j; k < i; k++) {
		vis[sg[j]^sg[k]] = 1;
	    }
	}
	for (int j = 0; ; j++)
	    if (!vis[j]) {
		sg[i] = j;
		break;
	    }
    }
}

void solve() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
	scanf("%d", &a[i]);
	if (a[i]&1) sum ^= sg[n - i - 1];
    }
    for (int i = 0; i < n; i++) {
	if (!a[i]) continue;
	for (int j = i + 1; j < n; j++) {
	    for (int k = j; k < n; k++) {
		if ((sum^sg[n - i - 1]^sg[n - j - 1]^sg[n - k - 1]) == 0) {
		    printf("%d %d %d\n", i, j, k);
		    return;
		}
	    }
	}
    }
    printf("-1 -1 -1\n");
}

int main() {
    int cas = 0;
    getsg();
    while (~scanf("%d", &n) && n) {
	printf("Game %d: ", ++cas);
	solve();
    }
    return 0;
}

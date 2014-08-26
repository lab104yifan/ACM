#include <cstdio>
#include <cstring>

const int N = 100005;
int t, n, a[N];

int solve() {
    int ans = 1;
    for (int i = 1; i < n; i++) {
	if ((a[i] == 2 && a[i - 1] == 1) || (a[i] == 1 && a[i - 1] == 2)) ans++;
	if (a[i] - a[i - 1] > 3 || a[i - 1] - a[i] > 3) return 0;
	if (a[i] == a[i - 1] && a[i] != 1) return 0;
    }
    if (a[n - 1]) ans *= 2;
    return ans;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	    scanf("%d", &a[i]);
	printf("Case #%d: %d\n", ++cas, solve());
    }
    return 0;
}

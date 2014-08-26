#include <cstdio>
#include <cstring>

const int N = 200005;

int t, n, m, a[N], q, ans[N];

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &m);
	int num;
	memset(a, 0, sizeof(a));
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < n; i++) {
	    scanf("%d", &num);
	    a[num]++;
	}
	int now = 200001;
	for (int i = 200001; i >= 1; i--) {
	    if (a[i] == 0)
		now = i;
	    ans[i] = now;
	}
	int q;
	while (m--) {
	    scanf("%d", &q);
	    printf("%d\n", ans[q]);
	}
    }
    return 0;
}

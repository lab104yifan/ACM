#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;

int n, q, a[N], l[N], r[N], num[N], cnt[N], v, rmq[N][20];

void init() {
    v = 0; int count, pre;
    scanf("%d", &q);
    for (int i = 0; i < n; i++) {
	scanf("%d", &a[i]);
	if (!i || a[i] != a[i - 1]) {
	    pre = i;
	    if (i)
		cnt[v++] = count;
	    count = 0;
	}
	count++;
	num[i] = v;
	l[i] = pre;
    }
    cnt[v++] = count;
    for (int i = n - 1; i >= 0; i--) {
	if (i == n - 1 || a[i] != a[i + 1]) {
	    pre = i;
	}
	r[i] = pre;
    }
}

void Build_RMQ(int* a, int n) {
    for (int i = 0; i < n; i++) rmq[i][0] = a[i];
    for (int j = 1; (1<<j) <= n; j++) {
	for (int i = 0; i + (1<<j) - 1 < n; i++) {
	    rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1<<(j - 1))][j - 1]);
	}
    }
}

int Query(int l, int r) {
    if (l > r) return 0;
    int k = 0;
    while ((1<<(k + 1)) <= r - l + 1) k++;
    return max(rmq[l][k], rmq[r - (1<<k) + 1][k]);
}

void solve() {
    Build_RMQ(cnt, v);
    int L, R;
    while (q--) {
	scanf("%d%d", &L, &R);
	L--; R--;
	if (num[L] == num[R]) printf("%d\n", R - L + 1);
	else printf("%d\n", max(Query(num[L] + 1, num[R] - 1), max(r[L] - L + 1, R - l[R] + 1)));
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
	init();
	solve();
    }
    return 0;
}

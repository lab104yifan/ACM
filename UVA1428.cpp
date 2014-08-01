#include <cstdio>
#include <cstring>

const int N = 100005;

int t, n, a[N];
long long bit[N], lx[N], rx[N];

inline int lowbit(int x) {
    return x&(-x);
}

void add(int x, long long val) {
    while (x < N) {
	bit[x] += val;
	x += lowbit(x);
    }
}

long long Query(int x) {
    long long ans = 0;
    while (x > 0) {
	ans += bit[x];
	x -= lowbit(x);
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	memset(bit, 0, sizeof(bit));
	for (int i = 0; i < n; i++) {
	    scanf("%d", &a[i]);
	    lx[i] = Query(a[i]);
	    add(a[i], 1);
	}
	memset(bit, 0, sizeof(bit));
	for (int i = n - 1; i >= 0; i--) {
	    rx[i] = Query(a[i]);
	    add(a[i], 1);
	}
	long long ans = 0;
	for (int i = 0; i < n; i++)
	    ans += lx[i] * (n - i - 1 - rx[i]) + (i - lx[i]) * rx[i];
	printf("%lld\n", ans);
    }
    return 0;
}

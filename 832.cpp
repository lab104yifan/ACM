#include <cstdio>
#include <cstring>

#define lowbit(x) (x&(-x))

const int N = 40005;

int n, m, num[N], bit[N];

void add(int x, int v) {
    while (x < N) {
	bit[x] += v;
	x += lowbit(x);
    }
}

int query(int x) {
    int ans = 0;
    while (x) {
	ans += bit[x];
	x -= lowbit(x);
    }
    return ans;
}

int lb[N], ls[N], rb[N], rs[N];

int main() {
    while (~scanf("%d%d", &n, &m)) {
	memset(bit, 0, sizeof(bit));
	int v;
	for (int i = 1; i <= n; i++) {
	    scanf("%d", &num[i]);
	    if (num[i] == m)
		v = i;
	}
	memset(lb, 0, sizeof(lb));
	memset(ls, 0, sizeof(ls));
	memset(rb, 0, sizeof(rb));
	memset(rs, 0, sizeof(rs));
	for (int i = v - 1; i >= 1; i--) {
	    add(num[i], 1);
	    int small = query(m);
	    int big = v - i - small;
	    if (big >= small)
		lb[big - small]++;
	    else ls[small - big]++;
	}
	memset(bit, 0, sizeof(bit));
	for (int i = v + 1; i <= n; i++) {
	    add(num[i], 1);
	    int small = query(m);
	    int big = i - v - small;
	    if (small >= big)
		rs[small - big]++;
	    else
		rb[big - small]++;
	}
	long long ans = 1;
	ans += lb[0] + rs[0];
	for (int i = 0; i <= 40000; i++) {
	    ans += (long long)lb[i] * rs[i];
	    ans += (long long)ls[i] * rb[i];
	}
	printf("%lld\n", ans);
    }
    return 0;
}

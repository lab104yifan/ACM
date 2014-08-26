#include <cstdio>
#include <cstring>

#define lowbit(x) (x&(-x))

const int N = 100005;

typedef long long ll;

int n, m;
ll bit[N], sum[N];

void add(int x, ll v) {
    while (x < N) {
	bit[x] += v;
	x += lowbit(x);
    }
}

ll get(int x) {
    ll ans = 0;
    while (x) {
	ans += bit[x];
	x -= lowbit(x);
    }
    return ans;
}

int main() {
    while (~scanf("%d", &n) && n) {
	memset(bit, 0, sizeof(bit));
	scanf("%d", &m);
	int l, r;
        ll d;
	while (m--) {
	    scanf("%d%d%I64d", &l, &r, &d);
	    add(r + 1, -d);
	    add(l, d);
	}
	sum[0] = 0;
	for (int i = 1; i <= n; i++)
	    sum[i] = sum[i - 1] + get(i);
	scanf("%d", &m);
	ll hp;
	int s;
	int ans = 0;
	while (m--) {
	    scanf("%I64d%d", &hp, &s);
	    if (sum[n] - sum[s - 1] < hp)
		ans++;
	}
	printf("%d\n", ans);
    }
    return 0;
}

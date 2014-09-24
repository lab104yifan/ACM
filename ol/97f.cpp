#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson(x) ((x<<1) + 1)
#define rson(x) ((x<<1) + 2)

const long long N = 200005;
typedef long long ll;
const ll MOD = 1000000007;

long long t, n;
char str[N];

struct Node {
	long long l, r;
	ll odd, even, sum1, sum2;
	ll size() {
		return r - l + 1;
	}
} node[N * 4];

void pushup(long long x) {
	if (node[lson(x)].size() % 2) {
		node[x].odd = (node[lson(x)].odd + node[rson(x)].even) % MOD;
		node[x].even = (node[lson(x)].even + node[rson(x)].odd) % MOD;
		node[x].sum1 = ((node[lson(x)].sum1 + node[rson(x)].size() * (node[lson(x)].odd % MOD) % MOD) % MOD + node[rson(x)].sum2) % MOD;
		node[x].sum2 = ((node[lson(x)].sum2 + node[rson(x)].size() * (node[lson(x)].even % MOD) % MOD) % MOD + node[rson(x)].sum1) % MOD;
	} else {
		node[x].odd = (node[lson(x)].odd + node[rson(x)].odd) % MOD;
		node[x].even = (node[lson(x)].even + node[rson(x)].even) % MOD;
		node[x].sum1 = ((node[lson(x)].sum1 + node[rson(x)].size() * (node[lson(x)].odd % MOD) % MOD) % MOD + node[rson(x)].sum1) % MOD;
		node[x].sum2 = ((node[lson(x)].sum2 + node[rson(x)].size() * (node[lson(x)].even % MOD) % MOD) % MOD + node[rson(x)].sum2) % MOD;
	}
}

void build(long long l, long long r, long long x = 0) {
	node[x].l = l; node[x].r = r;
	if (l == r) {
		node[x].odd = str[l] - '0';
		node[x].even = 0;
		node[x].sum1 = str[l] - '0';
		node[x].sum2 = 0;
		return;
	}
	long long mid = (l + r) / 2;
	build(l, mid, lson(x));
	build(mid + 1, r, rson(x));
	pushup(x);
}


void add(long long l, long long r, long long v, long long x = 0) {
	if (node[x].l >= l && node[x].r <= r) {
		node[x].odd = v;
		node[x].even = 0;
		node[x].sum1 = v;
		node[x].sum2 = 0;
		return;
	}
	long long mid = (node[x].l + node[x].r) / 2;
	if (l <= mid) add(l, r, v, lson(x));
	if (r > mid) add(l, r, v, rson(x));
	pushup(x);
}

Node get(long long l, long long r, long long tp, long long x = 0) {
	if (node[x].l >= l && node[x].r <= r)
		return node[x];
	long long mid = (node[x].l + node[x].r) / 2;
	if (l <= mid && r > mid) {
		Node ln = get(l, r, tp, lson(x));
		Node rn;
		Node ans;
		if (ln.size() % 2) {
			rn = get(l, r, !tp, rson(x));
			ans.l = ln.l;
			ans.r = rn.r;
			ans.odd = (ln.odd + rn.even) % MOD;
			ans.even = (ln.even + rn.odd) % MOD;
			ans.sum1 = ((ln.sum1 + rn.sum2) % MOD + rn.size() * (ln.odd % MOD) % MOD) % MOD;
			ans.sum2 = ((ln.sum2 + rn.sum1) % MOD + rn.size() * (ln.even % MOD) % MOD) % MOD;
		} else {
			rn = get(l, r, tp, rson(x));
			ans.l = ln.l;
			ans.r = rn.r;
			ans.odd = (ln.odd + rn.odd) % MOD;
			ans.even = (ln.even + rn.even) % MOD;
			ans.sum1 = ((ln.sum1 + rn.sum1) % MOD + rn.size() * (ln.odd % MOD) % MOD) % MOD;
			ans.sum2 = ((ln.sum2 + rn.sum2) % MOD + rn.size() * (ln.even % MOD) % MOD) % MOD;
		}
		return ans;
	} else if (l <= mid) return get(l, r, tp, lson(x));
	else if (r > mid) return get(l, r, tp, rson(x));
}

ll query(long long l, long long r, long long tp) {
	Node tmp = get(l, r, tp);
	if (tp == 0) return tmp.sum1;
	return tmp.sum2;
}

ll sum(ll a0, ll ti, ll an, ll d) {
	if (d == 0) return a0 % MOD * ti % MOD;
	ll ci = ti + 1;
	ll b = (a0 + an);
	if (b % 2 == 0)
		b /= 2;
	else if (ci % 2 == 0)
		ci /= 2;
	return b % MOD * (ci % MOD) % MOD;
}

ll solve(ll l, ll r) {
	ll s = l % n;
	ll e = r % n;
	if (s == 0) s = n;
	if (e == 0) e = n;
	ll ti = (r - e - (l + (n - s))) / n;
	if (ti < 0)
		return query(s, e, 0) % MOD;
	long long tp = 1;
	if ((n - s + 1) % 2) tp = 0;
	if (ti == 0) {
		Node ls = get((long long)s, n, 0);
		Node rs = get(1, (long long)e, tp);
		ll ans;
		if (tp) ans = (ls.sum1 + rs.sum1) % MOD;
		else ans = (ls.sum1 + rs.sum2) % MOD;
		ans = (ans + ls.odd * e) % MOD;
		return ans;
	}
	Node ls = get((long long)s, n, 0);
	Node mids = get(1, n, tp);
	Node rs = get(1, (long long)e, tp);
	ll ans;
	if (tp) ans = ((ls.sum1 + mids.sum1 % MOD * (ti % MOD) % MOD) % MOD + rs.sum1) % MOD;
	else ans = ((ls.sum1 + mids.sum2 % MOD * (ti % MOD) % MOD) % MOD +rs.sum2) % MOD;
	ll a0 = ls.odd;
	ll d;
	if (tp) d = mids.odd;
	else d = mids.even;
	ll an = a0 + (ti - 1) * d;
	ans = (ans + sum(a0, ti - 1, an, d) % MOD * n % MOD) % MOD;
	an += d;
	ans = (ans + an % MOD * e % MOD) % MOD;
	return ans;
}

int main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%s", str + 1);
		n = strlen(str + 1);
		for (long long i = 1; i <= n; i++)
			str[i + n] = str[i];
		n *= 2;
		build(1, n);
		long long q;
		scanf("%lld", &q);
		long long v, x, d;
		ll l, r;
		while (q--) {
			scanf("%lld", &v);
			if (v == 1) {
				scanf("%lld%lld", &x, &d);
				add(x, x, d);
				add(x + n / 2, x + n / 2, d);
			} else {
				scanf("%lld%lld", &l, &r);
				printf("%lld\n", solve(l, r));
			}
		}
	}
	return 0;
}

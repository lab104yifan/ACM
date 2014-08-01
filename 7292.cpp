#include <cstdio>
#include <cstring>
#include <cstdlib>

#define lson(x) ((x<<1) + 1)
#define rson(x) ((x<<1) + 2)

typedef __int64 ll;

const ll INF = 2000000000000000LL;
const int N = 100005;

int n, m, fn;
ll Fib[100];

struct Node {
    int l, r;
    ll sum;
    bool isFib;
} node[4 * N];

void pushup(int x) {
    int l = lson(x);
    int r = rson(x);
    node[x].l = node[l].l; node[x].r = node[r].r;
    node[x].isFib = (node[l].isFib && node[r].isFib);
    node[x].sum = node[l].sum + node[r].sum;
}

void build(int l, int r, int x) {
    if (l == r) {
	node[x].l = l;
	node[x].r = r;
	node[x].sum = 0;
	node[x].isFib = false;
	return;
    }
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
    pushup(x);
}

ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

ll find(ll x) {
    int l = 0, r = fn;
    while (l < r) {
	int mid = (l + r) / 2;
	if (Fib[mid] < x) l = mid + 1;
	else r = mid;
    }
    if (l == 0) return Fib[0];
    ll ll = Fib[l - 1], rr = Fib[l];
    if (abss(x - ll) <= abss(x - rr))
	return ll;
    else return rr;
}

void add(int k, ll v, int x) {
    if (node[x].l == k && node[x].r == k) {
	node[x].sum += v;;
	node[x].isFib = (find(node[x].sum) == node[x].sum);
	return;
    }
    int mid = (node[x].l + node[x].r) / 2;
    if (k <= mid) add(k, v, lson(x));
    if (k > mid) add(k, v, rson(x));
    pushup(x);
}

void insert(int l, int r, int x) {
    if (node[x].isFib) return;

    if (node[x].l == node[x].r) {
	node[x].sum = find(node[x].sum);
	node[x].isFib = true;
	return;
    }

    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) insert(l, r, lson(x));
    if (r > mid) insert(l, r, rson(x));
    pushup(x);
}

ll query(int l, int r, int x) {
    if (node[x].l >= l && node[x].r <= r)
	return node[x].sum;
    int mid = (node[x].l + node[x].r) / 2;
    ll ans = 0;
    if (l <= mid) ans += query(l, r, lson(x));
    if (r > mid) ans += query(l, r, rson(x));
    return ans;
}

int main() {
    Fib[0] = Fib[1] = 1;
    for (fn = 2; ; fn++) {
	Fib[fn] = Fib[fn - 2] + Fib[fn - 1];
	if (Fib[fn] > INF) break;
    }
    while (~scanf("%d%d", &n, &m)) {
	build(1, n, 0);
	int Q, a, b;
	ll v;
	while (m--) {
	    scanf("%d", &Q);
	    if (Q == 1) {
		scanf("%d%I64d", &a, &v);
		add(a, v, 0);
	    }
	    else if (Q == 2) {
		scanf("%d%d", &a, &b);
		printf("%I64d\n", query(a, b, 0));
	    }
	    else {
		scanf("%d%d", &a, &b);
		insert(a, b, 0);
	    }
	}
    }
    return 0;
}

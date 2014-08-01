#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;
#define lson(x) ((x<<1)+1)
#define rson(x) ((x<<1)+2)
#define INF 0x3f3f3f3f

int t, n, num[N];
struct Node {
    int l, r, x, setv;
    bool cover;
} node[4 * N];

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

void pushup(int x) {
    node[x].cover = ((node[lson(x)].x == node[rson(x)].x) && node[lson(x)].cover && node[rson(x)].cover);
    node[x].x = node[lson(x)].x;
}

void build(int l, int r, int x = 0) {
    node[x].l = l; node[x].r = r;
    node[x].setv = -1;
    node[x].cover = false;
    if (l == r) {
	node[x].cover = true;
	node[x].x = num[l];
	return;
    }
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
    pushup(x);
}

void pushdown(int x) {
    if (node[x].setv != -1) {
	node[lson(x)].setv = node[rson(x)].setv = node[x].setv;
	node[lson(x)].x = node[rson(x)].x = node[x].setv;
	node[x].setv = -1;
    }
}

void add1(int l, int r, int v, int x = 0) {
    if (node[x].l >= l && node[x].r <= r) {
	node[x].setv = v;
	node[x].x = v;
	return;
    }
    int mid = (node[x].l + node[x].r) / 2;
    pushdown(x);
    if (l <= mid) add1(l, r, v, lson(x));
    if (r > mid) add1(l, r, v, rson(x));
    pushup(x);
}

void add2(int l, int r, int v, int x = 0) {
    if (node[x].cover && node[x].x <= v) return;
    if (node[x].l >= l && node[x].r <= r && node[x].cover) {
	node[x].x = gcd(node[x].x, v);
	node[x].setv = node[x].x;
	return;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) add2(l, r, v, lson(x));
    if (r > mid) add2(l, r, v, rson(x));
    pushup(x);
}

int query(int k, int x = 0) {
    if (node[x].l == node[x].r)
	return node[x].x;
    int mid = (node[x].l + node[x].r) / 2;
    pushdown(x);
    if (k <= mid) return query(k, lson(x));
    if (k > mid) return query(k, rson(x));
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	    scanf("%d", &num[i]);
	build(1, n);
	int q;
	scanf("%d", &q);
	int c, a, b, v;
	while (q--) {
	    scanf("%d%d%d%d", &c, &a, &b, &v);
	    if (c == 1)
		add1(a, b, v);
	    else if (c == 2)
		add2(a, b, v);
	}
	for (int i = 1; i <= n; i++)
	    printf("%d ", query(i));
	printf("\n");
    }
    return 0;
}

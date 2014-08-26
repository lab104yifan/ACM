#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson(x) ((x<<1) + 1)
#define rson(x) ((x<<1) + 2)
#define INF 0x3f3f3f3f

const int N = 1000005;

struct Node {
    int l, r;
} node[4 * N];

void pushup(int x) {

}

void pushdown(int x) {

}

void build(int l, int r, int x) {
    node[x].l = l; node[x].r = r;
    if (l == r)
	return;
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
}

void add(int l, int r, int v, int x) {
    if (node[x].l >= l && node[x].r <= r) {
	return;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) add(l, r, v, lson(x));
    if (r > mid) add(l, r, v, rson(x));
    pushup(x);
}

void query(int l, int r, int x) {
    if (node[x].l >= l && node[x].r <= r) {
	return;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) query(l, r, lson(x));
    if (r > mid) query(l, r, rson(x));
}

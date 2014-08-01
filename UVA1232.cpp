#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson(x) ((x<<1)+1)
#define rson(x) ((x<<1)+2)

const int N = 100005;

int t, n;

struct Node {
    int l, r, h, setv;
    bool cover;
    Node() {}
    Node(int l, int r) {
	this->l = l; this->r = r;
	h = 0; setv = 0; cover = true;
    }
} node[4 * N];

void pushup(int x) {
    node[x].cover = ((node[lson(x)].h == node[rson(x)].h) && node[lson(x)].cover && node[rson(x)].cover);
    node[x].h = node[lson(x)].h;
}

void pushdown(int x) {
    node[lson(x)].setv = max(node[lson(x)].setv, node[x].setv);
    node[rson(x)].setv = max(node[rson(x)].setv, node[x].setv);
    node[lson(x)].h = max(node[lson(x)].setv, node[lson(x)].h);
    node[rson(x)].h = max(node[rson(x)].setv, node[rson(x)].h);
}

void build(int l, int r, int x = 0) {
    node[x] = Node(l, r);
    if (l == r) return;
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
}

int query(int l, int r, int v, int x = 0) {
    if (node[x].cover && node[x].h > v) return 0;
    if (node[x].l >= l && node[x].r <= r && node[x].cover) {
	node[x].setv = v;
	node[x].h = v;
	return node[x].r - node[x].l + 1;
    }
    int mid = (node[x].l + node[x].r) / 2;
    int ans = 0;
    pushdown(x);
    if (l <= mid) ans += query(l, r, v, lson(x));
    if (r > mid) ans += query(l, r, v, rson(x));
    pushup(x);
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	build(1, N - 1);
	int l, r, h;
	int ans = 0;
	while (n--) {
	    scanf("%d%d%d", &l, &r, &h);
	    ans += query(l, r - 1, h);
	}
	printf("%d\n", ans);
    }
    return 0;
}

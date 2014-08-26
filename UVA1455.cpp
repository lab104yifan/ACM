#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
#define lson(x) ((x<<1)+1)
#define rson(x) ((x<<1)+2)

const int N = 100005;
const int MAXN = 1000005;
struct Point {
    int x, y;
    void read() {
	scanf("%d%d", &x, &y);
    }
} p[N];

struct Node {
    int l, r, c, z, cv, zv;
    Node() {}
    Node (int l, int r) {
	this->l = l;
	this->r = r;
	c = z = cv = zv = 0;
    }
} node[4 * MAXN];

int t, n, parent[N], down[N], up[N], sum[N];

int find(int x) {
    return x == parent[x] ? x : parent[x] = find(parent[x]);
}

void pushup(int x) {
    node[x].c = node[lson(x)].c + node[rson(x)].c;
    node[x].z = node[lson(x)].z + node[rson(x)].z;
}

void pushdown(int x) {
    if (node[x].cv) {
	node[lson(x)].cv += node[x].cv;
	node[lson(x)].c += node[x].cv;
	node[rson(x)].cv += node[x].cv;
	node[rson(x)].c += node[x].cv;
	node[x].cv = 0;
    }
    if (node[x].zv) {
    	node[lson(x)].zv += node[x].zv;
	node[lson(x)].z += node[x].zv;
	node[rson(x)].zv += node[x].zv;
	node[rson(x)].z += node[x].zv;
	node[x].zv = 0;
    }
}

void build(int l, int r, int x = 0) {
    node[x] = Node(l, r);
    if (l == r)
	return;
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
}

void add(int l, int r, int type, int v, int x = 0) {
    if (l > r) return;
    if (node[x].l >= l && node[x].r <= r) {
	if (type == 1) {
	    node[x].zv += v;
	    node[x].z +=v;
	}
	else {
	    node[x].cv += v;
	    node[x].c += v;
	}
	return;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) add(l, r, type, v, lson(x));
    if (r > mid) add(l, r, type, v, rson(x));
    pushup(x);
}

void query(int k, int x = 0) {
    if (node[x].l == node[x].r) {
	printf("%d %d\n", node[x].z, node[x].c);
	return;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (k <= mid) query(k, lson(x));
    if (k > mid) query(k, rson(x));
    pushup(x);
}

void init() {
    int Maxy = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
	parent[i] = i;
	p[i].read();
	Maxy = max(Maxy, p[i].y);
	sum[i] = 1;
	down[i] = up[i] = p[i].y;
    }
    build(0, Maxy);
}

void solve() {
    int q;
    scanf("%d", &q);
    char c[10];
    int a, b;
    double x;
    while (q--) {
	scanf("%s", c);
	if (c[0] == 'r') {
	    scanf("%d%d", &a, &b);
	    int pa = find(a);
	    int pb = find(b);
	    if (pa != pb) {
		if (up[pb] > up[pa]) swap(pa, pb);
		if (down[pa] > up[pb]) {
		    add(up[pb], down[pa] - 1, 1, 1);
		    add(up[pb], down[pa] - 1, 2, sum[pa] + sum[pb]);
		    add(down[pa], up[pa] - 1, 2, sum[pb]);
		    add(down[pb], up[pb] - 1, 2, sum[pa]);
		}
		else {
		    add(up[pb], up[pa] - 1, 2, sum[pb]);
		    if (down[pa] < down[pb]) {
			add(down[pb], up[pb] - 1, 1, -1);
			add(down[pa], down[pb] - 1, 2, sum[pb]);
		    }
		    else {
			add(down[pa], up[pb] - 1, 1, -1);
			add(down[pb], down[pa] - 1, 2, sum[pa]);
		    }
		}
		parent[pa] = pb;
		sum[pb] += sum[pa];
		down[pb] = min(down[pb], down[pa]);
		up[pb] = max(up[pb], up[pa]);
	    }
	}
	else {
	    scanf("%lf", &x);
	    query((int)x);
	}
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
	init();
	solve();
    }
    return 0;
}

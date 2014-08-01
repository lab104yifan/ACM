#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson(x) ((x<<1) + 1)
#define rson(x) ((x<<1) + 2)
#define INF 0x3f3f3f3f

const int N = 1000005;

int r, c, m;

struct Node {
    int l, r;
    int sum, Max, Min, sumv, setv;
} node[4 * N];

void pushup(int x) {
    node[x].sum = node[lson(x)].sum + node[rson(x)].sum;
    node[x].Max = max(node[lson(x)].Max, node[rson(x)].Max);
    node[x].Min = min(node[lson(x)].Min, node[rson(x)].Min);
}

void pushdown(int x) {
    if (node[x].setv) {
	node[lson(x)].sumv = node[rson(x)].sumv = 0;
	node[lson(x)].setv = node[rson(x)].setv = node[x].setv;
	node[lson(x)].sum = (node[lson(x)].r - node[lson(x)].l + 1) * node[x].setv;
	node[rson(x)].sum = (node[rson(x)].r - node[rson(x)].l + 1) * node[x].setv;
	node[lson(x)].Max = node[lson(x)].Min = node[x].setv;
	node[rson(x)].Max = node[rson(x)].Min = node[x].setv;
	node[x].setv = 0;
    }
    if (node[x].sumv) {
	node[lson(x)].sumv += node[x].sumv;
	node[rson(x)].sumv += node[x].sumv;
	node[lson(x)].sum += (node[lson(x)].r - node[lson(x)].l + 1) * node[x].sumv;
	node[rson(x)].sum += (node[rson(x)].r - node[rson(x)].l + 1) * node[x].sumv;
	node[lson(x)].Max += node[x].sumv;
	node[lson(x)].Min += node[x].sumv;
	node[rson(x)].Max += node[x].sumv;
	node[rson(x)].Min += node[x].sumv;
	node[x].sumv = 0;
    }
}

void build(int l, int r, int x) {
    node[x].l = l; node[x].r = r;
    if (l == r) {
	node[x].sum = node[x].Max = node[x].Min = node[x].sumv = node[x].setv = 0;
	return;
    }
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
    pushup(x);
}

void add(int l, int r, int v, int x) {
    if (node[x].l >= l && node[x].r <= r) {
	node[x].sumv += v;
	node[x].sum += (node[x].r - node[x].l + 1) * v;
	node[x].Max += v;
	node[x].Min += v;
	return;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) add(l, r, v, lson(x));
    if (r > mid) add(l, r, v, rson(x));
    pushup(x);
}

void set(int l, int r, int v, int x) {
    if (node[x].l >= l && node[x].r <= r) {
	node[x].setv = v;
	node[x].sum = (node[x].r - node[x].l + 1) * v;
	node[x].Max = node[x].Min = v;
	node[x].sumv = 0;
	return;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) set(l, r, v, lson(x));
    if (r > mid) set(l, r, v, rson(x));
    pushup(x);
}

Node query(int l, int r, int x) {
    Node ans; ans.sum = 0; ans.Max = 0; ans.Min = INF;
    if (node[x].l >= l && node[x].r <= r) {
	ans.sum = node[x].sum;
	ans.Max = node[x].Max;
	ans.Min = node[x].Min;
	return ans;
    }
    pushdown(x);
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) {
	Node tmp = query(l, r, lson(x));
	ans.sum += tmp.sum;
	ans.Max = max(ans.Max, tmp.Max);
	ans.Min = min(ans.Min, tmp.Min);
    }
    if (r > mid) {
	Node tmp = query(l, r, rson(x));
	ans.sum += tmp.sum;
	ans.Max = max(ans.Max, tmp.Max);
	ans.Min = min(ans.Min, tmp.Min);
    }
    return ans;
}

int main() {
    while (~scanf("%d%d%d", &r, &c, &m)) {
	build(1, r * c, 0);
	int q, x1, y1, x2, y2, v;
	while (m--) {
	    scanf("%d", &q);
	    if (q == 3) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x1--; x2--;
		int sum = 0, Max = 0, Min = INF;
		for (int i = x1; i <= x2; i++) {
		    Node ans = query(i * c + y1, i * c + y2, 0);
		    sum += ans.sum;
		    Max = max(Max, ans.Max);
		    Min = min(Min, ans.Min);
		}
		printf("%d %d %d\n", sum, Min, Max);
	    }
	    else {
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
		x1--; x2--;
		for (int i = x1; i <= x2; i++) {
		    if (q == 1) add(i * c + y1, i * c + y2, v, 0);
		    else set(i * c + y1, i * c + y2, v, 0);
		}
	    }
	}
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson(x) ((x<<1) + 1)
#define rson(x) ((x<<1) + 2)
#define MP(a, b) make_pair(a, b)

typedef long long ll;
typedef pair<int, int> Point;

const int N = 500005;

int n, m;
ll a[N], sum[N];

struct Node {
    int l, r;
    int prex, sufx;
    Point sub;
} node[4 * N];

ll get(Point x) {
    return sum[x.second] - sum[x.first - 1];
}

bool Max(Point a, Point b) {
    long long sa = get(a);
    long long sb = get(b);
    if (sa != sb) return sa > sb;
    return a < b;
}

Point Maxsub(Node a, Node b) {
    Point ans;
    if (Max(a.sub, b.sub)) ans = a.sub;
    else ans = b.sub;
    if (Max(MP(a.sufx, b.prex), ans)) ans = MP(a.sufx, b.prex);
    return ans;
}

int Maxpre(Node a, Node b) {
    Point ans = MP(a.l, a.prex);
    if (Max(MP(a.l, b.prex), ans)) ans = MP(a.l, b.prex);
    return ans.second;
}

int Maxsuf(Node a, Node b) {
    Point ans = MP(b.sufx, b.r);
    if (Max(MP(a.sufx, b.r), ans)) ans = MP(a.sufx, b.r);
    return ans.first;
}

Node pushup(Node a, Node b) {
    Node ans;
    ans.l = a.l; ans.r = b.r;
    ans.sub = Maxsub(a, b);
    ans.prex = Maxpre(a, b);
    ans.sufx = Maxsuf(a, b);
    return ans;
}

void build(int l, int r, int x) {
    if (l == r) {
	node[x].l = l; node[x].r = r;
	node[x].prex = node[x].sufx = l;
	node[x].sub = MP(l, l);
	return ;
    }
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
    node[x] = pushup(node[lson(x)], node[rson(x)]);
}

Node Query(int l, int r, int x) {
    if (l <= node[x].l && r >= node[x].r)
	return node[x];
    int mid = (node[x].l + node[x].r) / 2;
    Node ans;
    if (l <= mid && r > mid)
	ans = pushup(Query(l, r, lson(x)), Query(l, r, rson(x)));
    else if (l <= mid) ans = Query(l, r, lson(x));
    else if (r > mid) ans = Query(l, r, rson(x));
    return ans;
}

int main() {
    int cas = 0;
    while (~scanf("%d%d", &n, &m)) {
	for (int i = 1; i <= n; i++) {
	    scanf("%lld", &a[i]);
	    sum[i] = sum[i - 1] + a[i];
	}
	build(1, n, 0);
	printf("Case %d:\n", ++cas);
	int a, b;
	while (m--) {
	    scanf("%d%d", &a, &b);
	    Node ans = Query(a, b, 0);
	    printf("%d %d\n", ans.sub.first, ans.sub.second);
	}
    }
    return 0;
}

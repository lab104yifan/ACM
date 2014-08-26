#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson(x) ((x<<1)+1)
#define rson(x) ((x<<1)+2)

typedef long long ll;
const int N = 100005;

struct Line {
    int l, r, h, flag;
    Line() {}
    Line(int l, int r, int h, int flag) {
	this->l = l; this->r = r;
	this->h = h; this->flag = flag;
    }
} li[N];

struct Point {
    int x1, y1, x2, y2;
} p[N];

bool cmp(Line a, Line b) {
    return a.h < b.h;
}

ll w, h;
int n, m, tot, hash[N], hn;

int find(int x) {
    int l = 0, r = hn - 1;
    while (l < r) {
	int mid = (l + r) / 2;
	if (hash[mid] < x) l = mid + 1;
	else r = mid;
    }
    return l;
}

void gethash() {
    hn = 0;
    for (int i = 0; i < tot; i++) {
	if (li[i].flag == 1) continue;
	hash[hn++] = li[i].l;
	hash[hn++] = li[i].r;
    }
    sort(hash, hash + hn);
    int tmp = hn;
    hn = 1;
    for (int i = 1; i < tmp; i++)
	if (hash[i] != hash[i - 1])
	    hash[hn++] = hash[i];
}

struct Node {
    int l, r, addv, len;
    Node() {}
    Node(int l, int r, int addv = 0, int len = 0) {
	this->l = l;
	this->r = r;
	this->addv = addv;
	this->len = len;
    }
} node[N * 4];

void build(int l, int r, int x = 0) {
    node[x] = Node(l, r);
    if (l == r)
	return;
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
}

void pushup(int x) {
    if (node[x].addv) node[x].len = hash[node[x].r + 1] - hash[node[x].l];
    else if (node[x].l == node[x].r) node[x].len = 0;
    else node[x].len = node[lson(x)].len + node[rson(x)].len;
}

void insert(int l, int r, int v, int x = 0) {
    if (node[x].l >= l && node[x].r <= r) {
	node[x].addv += v;
	pushup(x);
	return;
    }
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) insert(l, r, v, lson(x));
    if (r > mid) insert(l, r, v, rson(x));
    pushup(x);
}

ll solve() {
    if (n == 0) return h * (w - m + 1);
    ll ans = 0;
    sort(li, li + tot, cmp);
    gethash();
    build(0, hn - 2);
    for (int i = 0; i < tot; i++) {
	if (i) ans += (ll)node[0].len * (li[i].h - li[i - 1].h);
	insert(find(li[i].l), find(li[i].r) - 1, li[i].flag);
    }
    return h * w - ans;
}


ll init() {
    ll ans = 0;
    tot = 0;
    for (int i = 0; i < n; i++) {
	scanf("%d%d%d%d", &p[i].x1, &p[i].y1, &p[i].x2, &p[i].y2);
	li[tot++] = Line(max(0, p[i].x1 - m), p[i].x2, p[i].y1 - 1, 1);
	li[tot++] = Line(max(0, p[i].x1 - m), p[i].x2, p[i].y2, -1);
    }
    li[tot++] = Line(max(0, (int)w - m + 1), w, 0, 1);
    li[tot++] = Line(max(0, (int)w - m + 1), w, h, -1);
    ans += solve();
    tot = 0;
    for (int i = 0; i < n; i++) {
	li[tot++] = Line(max(0, p[i].y1 - m), p[i].y2, p[i].x1 - 1, 1);
	li[tot++] = Line(max(0, p[i].y1 - m), p[i].y2, p[i].x2, -1);
    }
    li[tot++] = Line(max(0, (int)h - m + 1), h, 0, 1);
    li[tot++] = Line(max(0, (int)h - m + 1), h, w, -1);
    swap(w, h);
    ans += solve();
    if (m == 1) ans /= 2;
    return ans;
}

int main() {
    while (~scanf("%lld%lld%d%d", &w, &h, &n, &m)) {
	printf("%lld\n", init());
    }
    return 0;
}

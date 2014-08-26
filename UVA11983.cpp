#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson(x) ((x<<1)+1)
#define rson(x) ((x<<1)+2)

const int N = 30005;

int hash[N * 2], hn;

int t, n, k;

struct Line {
    int l, r, y, flag;
    Line() {}
    Line(int l, int r, int y, int flag) {
	this->l = l;
	this->r = r;
	this->y = y;
	this->flag = flag;
    }
} line[N * 2];

bool cmp(Line a, Line b) {
    return a.y < b.y;
}

void init() {
    scanf("%d%d", &n, &k);
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++) {
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	x2++; y2++;
	hash[i] = x1; hash[i + n] = x2;
	line[i] = Line(x1, x2, y1, 1);
	line[i + n] = Line(x1, x2, y2, -1);
    }
    hn = 1;
    sort(hash, hash + 2 * n);
    for (int i = 1; i < 2 * n; i++) {
	if (hash[i] != hash[i - 1])
	    hash[hn++] = hash[i];
    }
    sort(line, line + 2 * n, cmp);
}

int F(int x) {
    int l = 0, r = hn - 1;
    while (l < r) {
	int mid = (l + r) / 2;
	if (hash[mid] < x) l = mid + 1;
	else r = mid;
    }
    return l;
}

struct Node {
    int l, r, sum[11], kv;
    Node() {}
    Node(int l, int r) {
	this->l = l;
	this->r = r;
	memset(sum, 0, sizeof(sum));
	kv = 0;
    }
} node[N * 8];

void build(int l, int r, int x = 0) {
    node[x] = Node(l, r);
    node[x].sum[0] = hash[r + 1] - hash[l];
    if (l == r)
	return;
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
}

void pushup(int x) {
    memset(node[x].sum, 0, sizeof(node[x].sum));
    if (node[x].l == node[x].r)
	node[x].sum[min(k, max(0, node[x].kv))] = hash[node[x].r + 1] - hash[node[x].l];
    else {
	for (int i = 0; i <= k; i++)
	    node[x].sum[min(k, max(0, i + node[x].kv))] += node[lson(x)].sum[i] + node[rson(x)].sum[i];
    }
}

void add(int l, int r, int v, int x = 0) {
    if (node[x].l >= l && node[x].r <= r) {
	node[x].kv += v;
	pushup(x);
	return;
    }
    int mid = (node[x].l + node[x].r) / 2;
    if (l <= mid) add(l, r, v, lson(x));
    if (r > mid) add(l, r, v, rson(x));
    pushup(x);
}

long long solve() {
    build(0, hn - 2); 
    long long ans = 0;
    for (int i = 0; i < 2 * n; i++) {
	if (i) ans += (long long)(line[i].y - line[i - 1].y) * node[0].sum[k];
	add(F(line[i].l), F(line[i].r) - 1, line[i].flag);
    }
    return ans;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	init();
	printf("Case %d: %lld\n", ++cas, solve());
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 205;
const int M = 50005;

struct OP {
    int c, xc, yc, a, b, v;
    OP(){}
    OP(int c, int xc, int yc, int a, int b, int v) {
	this->c = c; this->xc = xc; this->yc = yc;
	this->a = a; this->b = b; this->v = v;
    }
} op[M];

int parent[N][M];

int find(int *parent, int x) {
    return parent[x] == x ? x : parent[x] = find(parent, parent[x]);
}

int n, m, q, ans[10];

void init() {
    for (int i = 0; i < n; i++)
	for (int j = 0; j <= m; j++)
	    parent[i][j] = j;
    memset(ans, 0, sizeof(ans));
    char str[15];
    int a, b, c, d, e;
    for (int i = 0; i < q; i++) {
	scanf("%s", str);
	scanf("%d%d%d%d", &a, &b, &c, &d);
	if (str[0] == 'C')
	    op[i] = OP(0, a, b, c, 0, d);
	if (str[0] == 'D')
	    op[i] = OP(1, a, b, c, 0, d);
	if (str[0] == 'R') {
	    scanf("%d", &e);
	    op[i] = OP(2, a, b, c, d, e);
	}
	if (str[0] == 'T')
	    op[i] = OP(3, a, b, c, 0, d);
    }
}

void gao(int l, int r, int *parent, int v) {
    l = find(parent, l);
    while (l <= r) {
	ans[v]++;
	int tmp = find(parent, l + 1);
	parent[l] = tmp;
	l = tmp;
    }
}

void cir(int xc, int yc, int r, int v) {
    for (int i = max(0, xc - r); i <= min(n - 1, xc + r); i++) {
	int len = (int)(sqrt((r * r - (i - xc) * (i - xc))));
	int l = max(0, yc - len), r = min(m - 1, yc + len);
	gao(l, r, parent[i], v);
    }
}

void dia(int xc, int yc , int r, int v) {
    for (int i = max(0, xc - r); i <= min(n - 1, xc + r); i++) {
	int len = r - abs(i - xc);
	int l = max(0, yc - len), r = min(m - 1, yc + len);
	gao(l, r, parent[i], v);
    }
}

void rec(int xc, int yc, int h, int w, int v) {
    for (int i = max(0, xc); i <= min(n - 1, xc + h - 1); i++) {
	int l = max(0, yc), r = min(m - 1, yc + w - 1);
	gao(l, r, parent[i], v);
    }
}

void tri(int xc, int yc, int w, int v) {
    for (int i = max(0, xc); i <= min(n - 1, xc + (w + 1) / 2 - 1); i++) {
	int len = (w - 1) / 2 - i + xc;
	int l = max(0, yc - len), r = min(m - 1, yc + len);
	gao(l, r, parent[i], v);
    }
}

void solve() {
    for (int i = q - 1; i >= 0; i--) {
	if (op[i].c == 0)
	    cir(op[i].xc, op[i].yc, op[i].a, op[i].v);
	if (op[i].c == 1)
	    dia(op[i].xc, op[i].yc, op[i].a, op[i].v);
	if (op[i].c == 2)
	    rec(op[i].xc, op[i].yc, op[i].a, op[i].b, op[i].v);
	if (op[i].c == 3)
	    tri(op[i].xc, op[i].yc, op[i].a, op[i].v);
    }
    for (int i = 1; i <= 9; i++)
	printf("%d%c", ans[i], i == 9 ? '\n' : ' ');
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &q)) {
	init();
	solve();
    }
    return 0;
}

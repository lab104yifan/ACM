#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

#define lowbit(x) (x&(-x))

const int N = 200005;

struct Point {
    int x, y, rank, ans, Mi;
    int xn, yn;
} p[N];

int bit[N];
set<int> out;

void add(int x, int v) {
    while (x < N) {
	bit[x] += v;
	x += lowbit(x);
    }
}

int get(int x) {
    int ans = 0;
    while (x > 0) {
	ans += bit[x];
	x -= lowbit(x);
    }
    return ans;
}

int get(int l, int r) {
    return get(r) - get(l - 1);
}

bool cmpy(Point a, Point b) {
    return a.y < b.y;
}

bool cmpx(Point a, Point b) {
    if (a.x == b.x) return a.y > b.y;
    return a.x < b.x;
}

bool cmpx2(Point a, Point b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x > b.x;
}

int n, top;

void init() {
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < n; i++) {
	scanf("%d%d", &p[i].x, &p[i].y);
	p[i].ans = 0;
	p[i].xn = p[i].yn = 0;
    }
    sort(p, p + n, cmpy);
}

void solve() {
    top = 1;
    for (int i = 0; i < n; i++) {
	if (i && p[i].y != p[i - 1].y)
	    top++;
	p[i].rank = top;
	add(p[i].rank, 1);
    }
    for (int i = 0; i < n; i++) {
	int j;
	int len = 0;
	for (j = i; p[i].y == p[j].y && j < n; j++)
	    len++;
	for (j = i; p[i].y == p[j].y && j < n; j++)
	    p[j].yn = len;
	i = j - 1;
    }
    sort(p, p + n, cmpx);
    for (int i = 0; i < n; i++) {
	add(p[i].rank, -1);
	p[i].ans += get(p[i].rank + 1, top);
    }
    for (int i = 0; i < n; i++) {
	int j;
	int len = 0;
	for (j = i; p[i].x == p[j].x && j < n; j++)
	    len++;
	for (j = i; p[i].x == p[j].x && j < n; j++)
	    p[j].xn = len;
	i = j - 1;
    }
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < n; i++)
	add(p[i].rank, 1);
    sort(p, p + n, cmpx2);
    for (int i = 0; i < n; i++) {
	add(p[i].rank, -1);
	p[i].ans += get(1, p[i].rank - 1);
    }
    for (int i = 0; i < n; i++) {
	int j;
	int Min = 1000000000;
	for (j = i; p[i].x == p[j].x && j < n; j++)
	    Min = min(Min, p[j].ans);
	for (j = i; p[i].x == p[j].x && j < n; j++)
	    p[j].Mi = Min;
	i = j - 1;
    }
    int Max = 0;
    out.clear();
    for (int i = 0; i < n; i++) {
	if (p[i].Mi != p[i].ans) continue;
	if (p[i].ans > Max) {
	    Max = p[i].ans;
	    out.clear();
	    out.insert(n - p[i].ans - p[i].xn - p[i].yn + 1);
	}
	else if (p[i].ans == Max) {
	    out.insert(n - p[i].ans - p[i].xn - p[i].yn + 1);
	}
    }
    printf("Stan: %d; Ollie:", Max);
    for (set<int>::iterator it = out.begin(); it != out.end(); it++)
	printf(" %d", *it);
    printf(";\n");
}

int main() {
    while (~scanf("%d", &n) && n) {
	init();
	solve();
    }
    return 0;
}

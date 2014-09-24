#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;

struct Point {
	double v;
	int x, l, r, id;
	void read(int id) {
		scanf("%d%lf", &x, &v);
		this->id = id;
	}
} p[N];

bool cmp(Point a, Point b) {
	return a.x < b.x;
}

int t;
int n, m, k, to[N];

void build(int u) {
	int l = u, r = u;
	while (r - l != k) {
		if (l == 1) {
			r = k + 1;
			break;
		}
		if (r == n) {
			l = r - k;
			break;
		}
		if (p[u].x - p[l - 1].x < p[r + 1].x - p[u].x) l--;
		else if (p[u].x - p[l - 1].x > p[r + 1].x - p[u].x) r++;
		else {
			if (p[l - 1].id < p[r + 1].id) l--;
			else r++;
		}
	}
	p[u].l = l;
	p[u].r = r;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; i++)
			p[i].read(i);
		sort(p + 1, p + 1 + n, cmp);
		for (int i = 1; i <= n; i++) {
			to[p[i].id] = i;
			build(i);
		}
		int q;
		double ans = 0;
		while (m--) {
			scanf("%d", &q);
			int u = to[q];
			int l = p[u].l;
			int r = p[u].r;
			double sum = 0;
			for (int i = l; i <= r; i++) {
				if (u == i) continue;
				sum += p[i].v;
			}
			double add = sum / k;
			p[u].v = add;
			ans += add;
		}
		printf("%.6lf\n", ans);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 200005;
const double pi = acos(-1.0);
const double eps = 1e-8;

int t, n, q;
struct Build {
	double x, h;
	bool isq;
	double s[2];
	int id;
} b[N], Q[N];

bool cmp(Build a, Build b) {
	return a.x < b.x;
}

bool cmpid(Build a, Build b) {
	return a.id < b.id;
}

double cal(Build a, Build b) {
	double dx = fabs(b.x - a.x);
	double dy = b.h - a.h;
	return dy / dx;
}

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%lf%lf", &b[i].x, &b[i].h);
			b[i].isq = false;
			b[i].id = i;
		}
		scanf("%d", &q);
		for (int i = n; i < n + q; i++) {
			scanf("%lf", &b[i].x);
			b[i].h = 0;
			b[i].isq = true;
			b[i].id = i;
		}
		n += q;
		sort(b, b + n, cmp);
		Q[0] = b[0];
		int top = 0;
		int u = 0;
		for (int i = 1; i < n; i++) {
			if (b[i].isq == false) {
				while (top && cal(b[i], Q[top]) < cal(Q[top], Q[top - 1]))
					top--;
				Q[++top] = b[i];
			} else {
				int tmp = top;
				while (tmp && cal(b[i], Q[tmp]) < cal(b[i], Q[tmp - 1]))
					tmp--;
				b[i].s[u] = cal(b[i], Q[tmp]);
			}
		}
		reverse(b, b + n);
		Q[0] = b[0];
		top = 0;
		u = 1;
		for (int i = 1; i < n; i++) {
			if (b[i].isq == false) {
				while (top && cal(b[i], Q[top]) < cal(Q[top], Q[top - 1]))
					top--;
				Q[++top] = b[i];
			} else {
				int tmp = top;
				while (tmp && cal(b[i], Q[tmp]) < cal(b[i], Q[tmp - 1]))
					tmp--;
				b[i].s[u] = cal(b[i], Q[tmp]);
			}
		}
		sort(b, b + n, cmpid);
		printf("Case #%d:\n", ++cas);
		for (int i = 0; i < n; i++) {
			if (b[i].isq) {
				double ans = pi - atan(b[i].s[0]) - atan(b[i].s[1]);
				ans = ans / pi * 180;
				printf("%.10lf\n", ans);
			}
		}
	}
	return 0;
}

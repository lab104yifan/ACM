#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

struct Exp {
    int x[5], xn;
} ans[105];

int ansn, x[5];

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

bool cmp(Exp a, Exp b) {
    if (a.xn != b.xn)
	return a.xn < b.xn;
    return a.x[0] < b.x[0];
}

void solve2(int x0, int x1, int x2) {
    int flag = 1;
    int m1 = sqrt(abs(x0));
    int m2 = sqrt(abs(x2));
    for (int i = -m1; i <= m1; i++) {
	if (i == 0 || x0 % i) continue;
	for (int j = -m1; j <= m2; j++) {
	    if (j == 0 || x2 % j) continue;
	    int a = i, b = x0 / i, c = j, d = x2 / j;
	    if (a * d + c * b != x1) {
		swap(c, d);
		if (a * d + c * d != x1)
		    continue;
	    }
	    flag = 0;
	    ans[ansn].x[0] = a;
	    ans[ansn].x[1] = b;
	    ans[ansn++].xn = 2;
	    ans[ansn].x[0] = c;
	    ans[ansn].x[1] = d;
	    ans[ansn++].xn = 2;
	    return;
	}
    }
    if (flag) {
	ans[ansn].x[0] = x0;
	ans[ansn].x[1] = x1;
	ans[ansn].x[2] = x2;
	ans[ansn++].xn = 3;
    }
}

bool judge(int a, int &b ,int c, int d, int &e, int f) {
    int mu = c * d - a * f, zi = c * x[1] - a * x[3];
    if (zi % mu) return false;
    b = zi / mu;
    if ((x[1] - b * d) % a) return false;
    e = (x[1] - b * d) / a;
    if (c * d + b * e + a * f != x[2]) return false;
    return true;
}

void solve() {
    int flag = 1;
    int m1 = sqrt(abs(x[0]));
    int m2 = sqrt(abs(x[4]));
    for (int i = -m1; i <= m1; i++) {
	if (i == 0 || x[0] % i) continue;
	for (int j = -m2; j <= m2; j++) {
	    if (j == 0 || x[4] % j) continue;
	    int a = i, d = x[0] / i, c = j, f = x[4] / j;
	    int b, e;
	    if (!judge(a, b, c, d, e, f)) {
		swap(c, f);
		if (!judge(a, b, c, d, e, f))
		    continue;
	    }
	    flag = 0;
	    solve2(a, b, c);
	    solve2(d, e, f);
	    return;
	}
    }
    if (flag) {
	for (int i = 0; i < 5; i++)
	    ans[ansn].x[i] = x[i];
	ans[ansn++].xn = 5;
    }
}

void print() {
    sort(ans, ans + ansn, cmp);
    for (int i = 0; i < ansn; i++) {
	printf("%d", ans[i].x[0]);
	for (int j = 1; j < ans[i].xn; j++)
	    printf(" %d", ans[i].x[j]);
	printf("\n");
    }
    printf("\n");
}

int main() {
    while (~scanf("%d%d%d%d%d", &x[0], &x[1], &x[2], &x[3], &x[4])) {
	int f = 0;
	ansn = 0;
	for (int i = 0; i < 5; i++)
	    f = gcd(f, x[i]);
	int m = sqrt(f);
	for (int i = 2; i <= m && i <= f; i++) {
	    if (f % i == 0) {
		ans[ansn].x[0] = i;
		ans[ansn++].xn = 0;
	    }
	    while (f % i == 0)
		f /= i;
	}
	solve();
	print();
    }
    return 0;
}

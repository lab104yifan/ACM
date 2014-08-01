#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;

const double eps = 1e-9;
const double pi = acos(-1.0);
const int N = 205;
int n, ln;
struct Point {
    double x, y;
} p[N];

struct Line {
    double l, a, b, c, k, y;
} l[N * N];

bool cmpk(Line a, Line b) {
    return a.k < b.k;
}

bool cmpl(Line a, Line b) {
    return a.l < b.l;
}

bool cmpy(Line a, Line b) {
    if (fabs(a.y - b.y) < eps)
	return a.l < b.l;
    return a.y < b.y;
}

Line build(Point a, Point b) {
    Line ans;
    ans.l = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    ans.a = b.y - a.y, ans.b = a.x - b.x, ans.c = ans.a * a.x + ans.b * a.y;
    ans.k = atan2(ans.a, -ans.b);
    if (ans.k < 0 || fabs(ans.k) < eps) ans.k += pi;
    if (fabs(ans.b) < eps) ans.y = ans.c / ans.a;
    else ans.y = ans.c / ans.b;
    return ans;
}

long long C(long long n) {
    return n * (n - 1) / 2;
}

long long solve() {
    sort(l, l + ln, cmpk);
    long long ans = 0, cnt = 0;
    Line save[N * N];
    int sn = 0;
    l[ln++].k = -1;
    cnt = 0;
    for (int i = 0; i < ln; i++) {
	if (!i || fabs(l[i].k - l[i - 1].k) < eps) {
	    save[sn++] = l[i];
	    cnt++;
	    continue;
	}
	ans += C(cnt);
	cnt = 0;
	sort(save, save + sn, cmpl);
	for (int j = 0; j < sn; j++) {
	    if (!j || fabs(save[j - 1].l - save[j].l) < eps) {
		cnt++;
		continue;
	    }
	    ans -= C(cnt);
	    cnt = 1;
	}
	ans -= C(cnt);
	cnt = 0;
	sort(save, save + sn, cmpy);
	for (int j = 0; j < sn; j++) {
	    if (!j || fabs(save[j - 1].y - save[j].y) < eps) {
		cnt++;
		continue;
	    }
	    ans -= C(cnt);
	    cnt = 1;
	}
	ans -= C(cnt);
	cnt = 0;
	for (int j = 0; j < sn; j++) {
	    if (!j || (fabs(save[j - 1].y - save[j].y) < eps && fabs(save[j - 1].l - save[j].l) < eps)) {
		cnt++;
		continue;
	    }
	    ans += C(cnt);
	    cnt = 1;
	}
	ans += C(cnt);
	sn = 0;
	save[sn++] = l[i];
	cnt = 1;
    }
    return ans;
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	ln = 0;
	for (int i = 0; i < n; i++)
	    scanf("%lf%lf", &p[i].x, &p[i].y);
	for (int i = 0; i < n; i++) {
	    for (int j = i + 1; j < n; j++) {
		l[ln++] = build(p[i], p[j]);
	    }
	}
	printf("Case %d: %lld\n", ++cas, solve());
    }
    return 0;
}

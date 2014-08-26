#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

double pi = acos(-1.0);
double k, hb, db, hn, dn, h;
double v, rb, rn, hx;

void init() {
    v = 0;
    hx = h - hn - hb;
    rb = db / 2; rn = dn / 2;
    v += min(k, hb) * rb * rb * pi;
    if (k > hb) {
	double hz = hx * rb / (rb - rn);
	double ht = min(hx, k - hb);
	double rt = (hz - ht) / (hz - hx) * rb;
	v += 1.0 / 3 * ht * pi * (rb * rb + rt * rt + rb * rt);
    }
    if (k > h - hn)
	v += min(hn, (k - (h - hn))) * rn * rn * pi;
}

double cal1(double x, double rb, double hb) {
    double hh = rb - x;
    double r = acos(hh / rb);
    double ans = rb * rb * pi * hb * r / pi;
    double d = sqrt(rb * rb - hh * hh);
    ans -= d * hh * hb;
    return ans;
}

double cal2(double x) {
    double hz = hx * rb / (rb - rn);

    return ans;
}

double cal(double x) {
    double ans = 0;
    if (x > rb) {
	ans += rb * rb * pi * hb - cal1(db - x, rb, hb);
	ans += 1.0 / 3 * pi * (rb * rb + rn * rn + rb * rn) - cal2(db - x);
    }
    else {
	ans += cal1(x, rb, hb);
	ans += cal2(x);
    }
    x -= (rb - rn);
    if (x > 0) {
	if (x > dn) ans += rn * rn * pi * hn;
	else if (x > rn) ans += rn * rn * pi * hn - cal1(dn - x, rn, hn);
	else ans += cal1(x, rn, hn);
    }
    return ans;
}

double solve() {
    double l = 0, r = db;
    for (int i = 0; i < 100; i++) {
	double mid = (l + r) / 2;
	printf("%lf!!\n", cal(mid));
	if (cal(mid) > v) r = mid;
	else l = mid;
    }
    return l;
}

int main() {
    while (~scanf("%lf%lf%lf%lf%lf%lf", &k, &hb, &db, &hn, &dn, &h)) {
	if (!k && !hb && !db && !hn && !dn && !h) break;
	init();
	printf("%.2lf\n", solve());
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>

double r, R;

double h, x;

double cal(double a) {
    double d = a / 2;
    h = sqrt(R * R - d * d) + R;
    x = sqrt(h * h + d * d);
    return a * x * x / (2 * R * (a + x + x));
}

void solve() {
    double lx = 0, rx = sqrt(3.0) * R;
    double mid;
    for (int i = 0; i < 1000; i++) {
	mid = (lx + rx) / 2;
	double tmp = cal(mid);
	if (tmp > r) rx = mid;
	else lx = mid;
    }
    cal((lx + rx) / 2);
    printf("%.10lf %.10lf %.10lf\n", mid, x, x);
}

int main() {
    while (~scanf("%lf%lf", &r, &R)) {
	if (r * 2 > R) printf("NO Solution!\n");
	else solve();
    }
    return 0;
}

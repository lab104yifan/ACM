#include <cstdio>
#include <cstring>
#include <cmath>

const double pi = acos(-1.0);
double r, h;

double f(double x) {
    return r * r * x - 1.0 / 3 * x * x * x;
}

double solve() {
    double tot = r * r * pi * h * 2;
    if (r * 2 <= h) return tot - (f(r) - f(0)) * 8;
    h /= 2;
    double H = sqrt(r * r - h * h);
    return tot - (h * h * H + f(r) - f(H)) * 8;
}

int main() {
    while (~scanf("%lf%lf", &r, &h)) {
	printf("%.4lf\n", solve());
    }
    return 0;   
}

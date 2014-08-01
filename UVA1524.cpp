#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-9;
const int N = 105;

int n;
double a[N], s, e;

double F(double x) {
    double ans = 0;
    for (int i = 0; i < n; i++) {
	ans += a[i] * pow(x, i);
    }
    return ans;
}

double simpon(double a, double b) {
    double c = (a + b) / 2;
    return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}

double asr(double a, double b, double eps, double A) {
    double c = (a + b) / 2;
    double L = simpon(a, c), R = simpon(c, b);
    if (L + R - A <= 15 * eps) return L + R + (L + R - A) / 15.0;
    return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}

int main() {
    while (~scanf("%d", &n) && n) {
	for (int i = n; i >= 0; i--)
	    scanf("%lf", &a[i]);
	for (int i = 0; i < n; i++)
	    a[i] = a[i + 1] * i;
	scanf("%lf%lf", &s, &e);
	printf("%.3lf\n", asr(s, e, eps, simpon(s, e)) / (e - s));
    }
    return 0;
}

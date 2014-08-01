#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-8;

int t;
double d, h, b, l, m, w;

inline double F(double x) {
    double a = 4 * m / w / w;
    return sqrt(1 + 4 * a * a * x * x);
}

inline double simpson(double fa, double fb, double fc, double a, double c) {
    return (fa + 4 * fb + fc) * (c - a) / 6;
}

double asr(double a, double b, double c, double esp, double A, double fa, double fb, double fc) {
    double ab = (a + b) / 2, bc = (b + c) / 2;
    double fab = F(ab), fbc = F(bc);
    double L = simpson(fa, fab, fc, a, b), R = simpson(fb, fbc, fc, b, c);
    if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.0;
    return asr(a, ab, b, esp / 2, L, fa, fab, fb) + asr(b, bc, c, esp / 2, R, fb, fbc, fc);
}

double asr(double a, double c, double eps) {
    double b = (a + c) / 2;
    double fa = F(a), fb = F(b), fc = F(c);
    return asr(a, b, c, eps, simpson(fa, fb, fc, a, c), fa, fb, fc);
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%lf%lf%lf%lf", &d, &h, &b, &l);
	double n = ceil(b / d);
	l = l / n; w = b / n;
	double x = 0, y = h;
	while (fabs(x - y) > eps) {
	    m = (x + y) / 2;
	    if (2 * asr(0, w / 2, eps) < l) x = m;
	    else y = m;
	}
	printf("Case %d:\n%.2lf\n", ++cas, h - x);
	if (t) printf("\n");
    }
    return 0;
}

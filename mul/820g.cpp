#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-8;
int T;
double v1, v2, r, d;

inline double F(double x) {
    return 1.0 / sqrt(v2 * v2 - v1 * v1 / r / r * x * x);
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
    scanf("%d", &T);
    while (T--) {
	scanf("%lf%lf%lf%lf", &v1, &v2, &r, &d);
	if (fabs(v1 - v2) < eps || asr(0, r, eps) * v2 > d) printf("Why give up treatment\n");
	else printf("Wake up to code\n");
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>

const double pi = acos(-1.0);

double l, n, c;

double cal(double r) {
    return l / sin(r) * r;
}

int main() {
    while (~scanf("%lf%lf%lf", &l, &n, &c)) {
	if (l < 0) break;
	double x = 0, y = pi / 2, lx = (1 + n * c) * l, m;
	for (int i = 0; i < 100; i++) {
	    m = (x + y) / 2;
	    if (cal(m) < lx) x = m;
	    else y = m;
	}
	printf("%.3lf\n", l / 2 / sin(m) * (1 - cos(m)));
    }
    return 0;
}

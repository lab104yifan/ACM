#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-9;
const double pi = acos(-1.0);

double a, b, c, d;

double solve() {
	if (fabs(a) < eps)
		return 0.0;
	if (fabs(c) < eps)
		return 0.0;
	if (fabs(b) < eps)
		return c;
	if (fabs(d) < eps)
		return b + c;
	a = a / 180 * pi; b = b / 180 * pi; c = c / 180 * pi; d = d / 180 * pi;
	double AB = 1.0;
	double AOB = pi - b - c;
	double ADB = pi - a - b - c;
	double AEB = pi - b - c - d;
	double A = a + b, B = c + d;
	double AO = AB * sin(c) / sin(AOB);
	double BO = AB * sin(b) / sin(AOB);
	double BD = AB * sin(A) / sin(ADB);
	double AE = AB * sin(B) / sin(AEB);
	double DO = BD - BO;
	double EO = AE - AO;
	double DE = sqrt(DO * DO + EO * EO - cos(AOB) * 2 * DO * EO);
	double cosx = (DE * DE + EO * EO - DO * DO) / 2 / DE / EO;
	double ans = acos(cosx) * 180 / pi;
	return ans;
}

int main() {
	while (~scanf("%lf%lf%lf%lf", &a, &b, &c, &d)) {
		printf("%.2lf\n", solve());
	}
	return 0;
}

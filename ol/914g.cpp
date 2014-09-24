#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

double a, b, c, d, e, f;
const double eps = 1e-12;

double dis(double x, double y, double z) {
	return sqrt(x * x + y * y + z * z);
}

double dcmp(double x) {
	if (fabs(x) < eps) return 0.0;
	return x;
}

double cal(double x, double y) {
	double A = c;
	double B = d * y + e * x;
	double C = f * x * y + a * x * x + b * y * y - 1;
	double del = sqrt(dcmp(B * B - 4 * A * C));
	double z1 = (-B + del) / A / 2;
	double z2 = (-B - del) / A / 2;
	return min(dis(x, y, z1), dis(x, y, z2));
}

double solve(double x) {
	double A = b;
	double B = f * x;
	double C = a * x * x - 1;
	double del = sqrt(dcmp(B * B - 4 * A * C));
	double l = (-B - del) / A / 2, r = (-B + del) / A / 2;
	while (r - l > eps) {
		double midl = (l * 2 + r) / 3;
		double midr = (l + 2 * r) / 3;
		if (cal(x, midl) < cal(x, midr)) r = midr;
		else l = midl;
	}
	return cal(x, l);
}

int main() {
	while (~scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f)) {
		double tmp = sqrt(1.0 / a);
		double l = -tmp, r = tmp;
		while (r - l > eps) { 
			double midl = (l * 2 + r) / 3;
			double midr = (l + 2 * r) / 3;
			if (solve(midl) < solve(midr)) r = midr;
			else l = midl;
		}
		printf("%.7lf\n", solve(l));
	}
	return 0;
}

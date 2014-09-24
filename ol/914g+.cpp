#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int D[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
double a, b, c, d, e, f;
const double INF = 1e9;
const double eps = 1e-8;

double dis(double x, double y, double z) {
	return sqrt(x * x + y * y + z * z);
}

double cal(double x, double y) {
	double A = c;
	double B = d * y + e * x;
	double C = f * x * y + a * x * x + b * y * y - 1;
	double del = B * B - 4 * A * C;
	if (del < 0) return 1e10;
	del = sqrt(del);
	double z1 = (-B + del) / A / 2;
	double z2 = (-B - del) / A / 2;
	if (dis(x, y, z1) < dis(x, y, z2)) return z1;
	return z2;
}

double solve() {
	double x = 0, y = 0, z = sqrt(1.0 / c);
	double step = 1.0, r = 0.99;
	while (step > eps) {
		for (int i = 0; i < 8; i++) {
			double xx = x + step * D[i][0];
			double yy = y + step * D[i][1];
			double zz = cal(xx, yy);
			if (zz > INF) continue;
			if (dis(xx, yy, zz) < dis(x, y, z)) {
				x = xx; y = yy; z = zz;
			}
		}
		step *= r;
	}
	return dis(x, y, z);
}

int main() {
	while (~scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f)) {
		printf("%.7lf\n", solve());
	}
	return 0;
}

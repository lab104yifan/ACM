#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-9;
const int N = 105;
int n;
double a[N], fa[N], s, e;

double F(double x) {
    double ans = 0;
    for (int i = 0; i <= n; i++)
	ans += fa[i] * pow(x, i + 1);
    return ans;
}

double cal(double *f, double x, int n) {
    double ans = 0;
    for (int i = 0; i <= n; i++)
	ans += f[i] * pow(x, i);
    return ans;
}

double newton(double *f, int n) {
    double fd[N];
    for (int i = 0; i < n; i++)
	fd[i] = f[i + 1] * (i + 1);
    double x = -eps;
    for (int i = 0; i < 100; i++)
	x = x - cal(f, x, n) / cal(fd, x, n - 1);
    return x;
}

void tra(double *f, double x, int n) {
    f[n + 1] = 0;
    for (int i = n; i > 0; i--)
	f[i] = f[i + 1] * x + f[i];
    for (int i = 0; i < n; i++)
	f[i] = f[i + 1];
}

double solve() {
    double ans = 0;
    double v[N]; int vn = 0;
    v[vn++] = s; v[vn++] = e;
    for (int i = 0; i < n; i++) {
	double x = newton(a, n - i);
	if (x > s && x < e) v[vn++] = x;
	tra(a, x, n - i);
    }
    sort(v, v + vn);
    for (int i = 1; i < vn; i++)
	ans += fabs(F(v[i]) - F(v[i - 1]));
    return ans / (e - s);
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	for (int i = n; i >= 0; i--)
	    scanf("%lf", &a[i]);
	scanf("%lf%lf", &s, &e);
	for (int i = n; i >= 0; i--)
	    fa[i] = a[i] / (i + 1);
	printf("%.3lf\n", solve());
    }
    return 0;
}

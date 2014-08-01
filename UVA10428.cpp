#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 10;
int n;
double a[N];

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
    double x = -25.0;
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

void solve() {
    for (int i = 0; i < n; i++) {
	double x = newton(a, n - i);
	printf(" %.4lf", x);
	tra(a, x, n - i);
    }
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	for (int i = n; i >= 0; i--)
	    scanf("%lf", &a[i]);
	printf("Equation %d:", ++cas);
	solve();
	printf("\n");
    }
    return 0;
}

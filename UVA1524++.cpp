#include <cstdio>
#include <cstring>
#include <cmath>

const int N = 105;

int n;
double a[N], s, e;

double F(double x) {
    double ans = 0;
    for (int i = 0; i <= n; i++)
	ans += a[i] * pow(x, i + 1);
    return ans;
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	for (int i = n; i >= 0; i--) {
	    scanf("%lf", &a[i]);
	    a[i] = a[i] / (i + 1);
	}
	scanf("%lf%lf", &s, &e);
	printf("%.3lf\n", (F(e) - F(s)) / (e - s));
    }
    return 0;
}

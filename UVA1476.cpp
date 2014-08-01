#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 10005;
int t, n, ans;
struct Line {
    double a, b, c;
} l[N];

double cal(double x) {
    double ans = l[0].a * x * x + l[0].b * x + l[0].c;
    for (int i = 1; i < n; i++)
	ans = max(ans, l[i].a * x * x + l[i].b * x + l[i].c);
    return ans;
}

double solve() {
    double l = 0, r = 1000;
    while (fabs(l - r) > 1e-9) {
	double ml = (2 * l + r) / 3;
	double mr = (l + 2 * r) / 3;
	if (cal(ml) < cal(mr)) r = mr;
	else l = ml;
    }
    return cal(l);
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	    scanf("%lf%lf%lf", &l[i].a, &l[i].b, &l[i].c);
	printf("%.4lf\n", solve());
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 55;
const double eps = 1e-9;
int t, n;
double a[N];

bool notless(double a, double b) {
    if (fabs(a - b) < eps) return true;
    return a > b;
}

bool judge(double len) {
    int flag = 1;
    for (int i = 2; i < n; i++) {
	if (flag && notless(a[i] - a[i - 1], len))
	    continue;
	else if (flag && a[i] - a[i - 1] < len && notless(a[i + 1] - a[i], len * 2))
	    continue;
	else if (flag && a[i] - a[i - 1] < len && notless(a[i + 1] - a[i], len)) {
	    if (fabs(a[i + 1] - a[i] - len) >= eps)
		flag = 0;
	    continue;
	}
	else if (!flag && notless(a[i + 1] - a[i], len * 2)) {
	    flag = 1;
	    continue;
	}
	else if (!flag && notless(a[i + 1] - a[i], len)) {
	    if (fabs(a[i + 1] - a[i] - len) < eps)
		flag = 1;
	    continue;
	}
	return false;
    }
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	    scanf("%lf", &a[i]);
	sort(a + 1, a + 1 + n);
	double ans = 0;
	for (int i = 1; i < n; i++) {
	    double len = a[i + 1] - a[i];
	    if (judge(len))
		ans = max(ans, len);
	    len /= 2;
	    if (judge(len))
		ans = max(ans, len);
	}
	printf("%.3lf\n", ans);
    }
    return 0;
}

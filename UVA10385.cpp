#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 25;

double t, v1[N], v2[N];
int n;

double cal(double r) {
    double k = t - r;
    double ans = 1e100;
    double t1 = r / v1[n - 1] + k / v2[n - 1];
    for (int i = 0; i < n - 1; i++) {
	double t2 = r / v1[i] + k / v2[i];
	ans = min(ans, t2 - t1);
    }
    return ans;
}

int main() {
    while (~scanf("%lf", &t)) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	    scanf("%lf%lf", &v1[i], &v2[i]);
	double l = 0, r = t;
	for (int i = 0; i < 100; i++) {
	    double midl = (l * 2 + r) / 3;
	    double midr = (l + r * 2) / 3;
	    if (cal(midl) > cal(midr)) r = midr;
	    else l = midl;
	}
	double ti = cal(l);
	if (cal(l) < 0.00) printf("The cheater cannot win.\n");
	else printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n", ti * 3600, l, t - l);
    }
    return 0;
}

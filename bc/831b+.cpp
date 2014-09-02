#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1000005;

int n, m;

double a[N];

int main() {
	for (int i = 1; i <= 1000000; i++)
		a[i] = a[i - 1] + 1.0/i;
	while (~scanf("%d", &n)) {
		int up = min(n, 1000000);
		double ans = a[up];
		if (n > up)
			ans += log((n + 1.) / up);
		printf("%.4lf\n", ans);
	}
	return 0;
}

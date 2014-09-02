#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1000005;
const double sb = 0.577215664901;

int n;

double ans[N];

int main() {
	for (int i = 1; i < N; i++)
		ans[i] = ans[i - 1] + 1.0 / i;
	while (~scanf("%d", &n)) {
		if (n >= N) printf("%.4lf\n", sb + log(n * 1.0));
		else printf("%.4lf\n", ans[n]);
	}
	return 0;
}

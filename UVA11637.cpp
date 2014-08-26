#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 100005;

int n, k;
long double frc[N];

double solve(int n, int k) {
    if (n == 1) return 0.0;
    if (n - 2 * k - 1 <= 0) return n * 1.0;
    double ans = 0;
    for (int i = 1; i <= n; i++) {
	int x = max(i - k - 1, 0) + max(n - (i + k), 0);
	if (x >= 2 * k)
	    ans += exp(frc[x] - frc[x - 2 * k] + frc[n - 2 * k - 1] - frc[n - 1]);
    }
    return n * 1.0 - ans;
}

int main() {
    int cas = 0;
    for (int i = 1; i < N; i++)
	frc[i] = frc[i - 1] + log((long double)i);
    while (~scanf("%d%d", &n, &k) && n || k) {
	printf("Case %d: %.4lf\n", ++cas, solve(n, k));
    }
    return 0;
}

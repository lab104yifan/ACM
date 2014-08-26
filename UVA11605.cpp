#include <cstdio>
#include <cstring>
#include <cmath>

int t, n, m, p, K;

double cal(double P) {
    return (1 - pow(1 - 2 * P, K)) / 2;
}

double solve() {
    double ans = 0;
    for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= m; j++) {
	    for (int k = 1; k <= p; k++) {
		int x = (n - i + 1) * i;
		int y = (m - j + 1) * j;
		int z = (p - k + 1) * k;
		double P = (2 * x * 1.0 - 1) / (m * n * p) * (2 * y - 1) / (m * n * p) * (2 * z - 1);
		ans += cal(P);
	    }
	}
    }
    return ans;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d%d%d", &n, &m, &p, &K);
	printf("Case %d: %.10lf\n", ++cas, solve());
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int t, avg, n;
double dp1[15][405], dp2[15][405];

double get(int x) {
    if (x >= 25 && x <= 40) return 4.0;
    if (x >= 20 && x <= 24) return 3.5;
    if (x >= 15 && x <= 19) return 3.0;
    if (x >= 10 && x <= 14) return 2.5;
    return 2.0;
}

void init() {
    for (int i = 1; i <= 400; i++)
	dp2[0][i] = 50;
    for (int i = 1; i <= 10; i++) {
	for (int j = 0; j <= 400; j++) {
	    dp1[i][j] = 0;
	    dp2[i][j] = 50;
	    for (int k = 0; k <= j && k <= 40; k++) {
		dp1[i][j] = max(dp1[i][j], dp1[i - 1][j - k] + get(k));
		dp2[i][j] = min(dp2[i][j], dp2[i - 1][j - k] + get(k));
	    }
	}
    }
}

int main() {
    init();
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &avg, &n);
	avg = (avg - 60) * n;
	printf("%.4lf %.4lf\n", dp2[n][avg] / n, dp1[n][avg] / n);
    }
    return 0;
}

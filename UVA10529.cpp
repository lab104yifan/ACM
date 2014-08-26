#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
const int N = 1000005;
int n;
double p, pl, pr, dp[N];

double cal(int l, int r) {
    return dp[l] + dp[r] + (pl * dp[l] + pr * dp[r] + 1) / p;
}

double solve() {
    p = 1 - pl - pr;
    dp[0] = 0; dp[1] = 1 / p;
    int pre = 0;
    for (int i = 2; i <= n; i++) {
	dp[i] = cal(pre, i - pre - 1);
	for (int j = pre + 1; j < i; j++) {
	    int l = j, r = i - 1 - j;
	    double tmp = cal(l, r);
	    if (dp[i] >= tmp) {
		dp[i] = tmp;
		pre = j;
	    }
	    else break;
	}
    }
    return dp[n];
}

int main() {
    while (~scanf("%d", &n) && n) {
	scanf("%lf%lf", &pl, &pr);
	printf("%.2lf\n", solve());	
    }
    return 0;
}

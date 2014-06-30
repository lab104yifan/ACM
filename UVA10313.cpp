#include <stdio.h>
#include <string.h>

int n, a, b, i, j, k;
long long dp[305][305], ans;
char sb[20];

int min(int a, int b) {
    return a < b ? a : b;
}
int main() {
    dp[0][0] = 1;
    for (i = 1; i <= 300; i ++) {
	for (j = i; j <= 300; j ++) {
	    for (k = 1; k <= 300; k ++) {
		dp[j][k] += dp[j - i][k - 1];
	    }
	}
    }
    while (gets(sb) != NULL) {
	a = b = -1; ans = 0;
	sscanf(sb, "%d%d%d", &n, &a, &b);
	a = min(a, 300); b = min(b, 300);
	if (a == -1) {
	    for (i = 0; i <= n; i ++) {
		ans += dp[n][i];
	    }
	}
	else if (b == -1) {
	    for (i = 0; i <= a; i ++) {
		ans += dp[n][i];
	    }
	}
	else {
	    for (i = a; i <= b; i ++) {
		ans += dp[n][i];
	    }
	}
	printf("%lld\n", ans);
    }
    return 0;
}

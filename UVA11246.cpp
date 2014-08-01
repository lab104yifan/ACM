#include <stdio.h>
#include <string.h>

int t, n, k;

int solve(int n, int k) {
    int sign = 1, ans = 0;
    while (n) {
	ans += sign * n;
	n /= k;
	sign = - sign;
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &k);
	printf("%d\n", solve(n, k));
    }
    return 0;
}

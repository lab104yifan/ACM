#include <stdio.h>
#include <string.h>

const int N = 225;
long long C[N][N];
int t;
long long n, m, k;

void solve(long long k) {
    for (long long  i = 1; i < n; i++) {
	long long sum = 0;
	for (long long j = 1; j <= m - (n - i); j++) {
	    if (sum + C[m - j - 1][n - i - 1] < k)
		sum += C[m - j - 1][n - i - 1];
	    else {
		printf("%lld\n", j);
		m -= j;
		k -= sum;
		break;
	    }
	}
    }
    printf("%lld\n", m);
}

int main() {
    for (int i = 0; i <= 220; i++) {
	C[i][0] = C[i][i] = 1;
	for (int j = 1; j < i && j <= 10; j++) {
	    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
    }
    scanf("%d", &t);
    while (t--) {
	scanf("%lld%lld%lld", &m, &n, &k);
	solve(k);
    }
    return 0;
}

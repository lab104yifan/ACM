#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 45;

int t, a, b, c, n;
ll C[N][N];

void getC() {
    for (int i = 0; i <= 40; i++) {
	C[i][0] = C[i][i] = 1;
	for (int j = 1; j < i; j++)
	    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

int gcd(int a, int b) {
    while (b) {
	int tmp = b;
	b = a % b;
	a = tmp;
    }
    return a;
}

ll cal(int a, int b, int c, int d, int len) {
    if (a < 0 || b < 0 || c < 0) return 0;
    if (a % len || b % len || c % len) return 0;
    int az = a / len, bz = b / len;
    return C[d][az] * C[d - az][bz];
}

int main() {
    getC();
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d%d", &a, &b, &c);
	n = a + b + c;
	ll ans = 0;
	for (int i = 0; i < n; i++) {
	    int d = gcd(i, n);
	    int len = n / d;
	    ans += cal(a, b, c, d, len);
	}
	if (n&1) {
	    ans += cal(a - 1, b, c, n / 2, 2) * n;
	    ans += cal(a, b - 1, c, n / 2, 2) * n;
	    ans += cal(a, b, c - 1, n / 2, 2) * n;
	}
	else {
	    ans += cal(a, b, c, n / 2, 2) * (n / 2);
	    ans += cal(a - 1, b - 1, c, n / 2 - 1, 2) * n;
	    ans += cal(a - 1, b, c - 1, n / 2 - 1, 2) * n;
	    ans += cal(a, b - 1, c - 1, n / 2 - 1, 2) * n;
	    ans += cal(a - 2, b, c, n / 2 - 1, 2) * (n / 2);
	    ans += cal(a, b - 2, c, n / 2 - 1, 2) * (n / 2);
	    ans += cal(a, b, c - 2, n / 2 - 1, 2) * (n / 2);
	}
	ans /= 2 * n;
	printf("%lld\n", ans);
    }
    return 0;
}

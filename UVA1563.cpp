#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 105;

int pow_mod(int x, int k, int mod) {
    int ans = 1;
    while (k) {
	if (k&1) ans = ans * x % mod;
	x = x * x % mod;
	k >>= 1;
    }
    return ans;
}

int inv(int a, int n) {
    return pow_mod(a, n - 2, n);
}

int t, p, n, A[N][N];
char str[N];

int hash(int c) {
    if (c == '*') return 0;
    return c - 'a' + 1;
}

void build() {
    for (int i = 0; i < n; i++) {
	A[i][n] = hash(str[i]);
	int tmp = 1;
	for (int j = 0; j < n; j++) {
	    A[i][j] = tmp;
	    tmp = tmp * (i + 1) % p;
	}
    }
}

void gauss() {
    for (int i = 0; i < n; i++) {
	int r;
	for (r = i; r < n; i++)
	    if (A[r][i]) break;
	if (r == n) continue;
	for (int j = i; j <= n; j++) swap(A[r][j], A[i][j]);
	for (int j = 0; j < n; j++) {
	    if (i == j) continue;
	    if (A[j][i]) {
		int tmp = A[j][i] * inv(A[i][i], p) % p;
		for (int k = i; k <= n; k++) {
		    A[j][k] = (((A[j][k] - tmp * A[i][k]) % p) + p) % p;
		}
	    }
	}
    }
    for (int i = 0; i < n; i++)
	printf("%d%c", A[i][n] * inv(A[i][i], p) % p, i == n - 1 ? '\n' : ' ');
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%s", &p, str);
	n = strlen(str);
	build();
	gauss();
    }
    return 0;
}

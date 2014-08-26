#include <cstdio>
#include <cstring>

typedef unsigned long long ull;

const ull X1 = 100000007, X2 = 1000000007;

const int N = 1005;
const int M = 105;

int t, n, m, x, y;
char a[N][N], b[M][M];
ull H[N][N];

ull gethash() {
    ull ans = 0;
    for (int i = 0; i < x; i++) {
	ull u = 0;
	for (int j = 0; j < y; j++)
	    u = u * X1 + b[i][j];
	ans = ans * X2 + u;
    }
    return ans;
}

int solve() {
    ull u = gethash(), Hp = 1;
    for (int i = 0; i < y - 1; i++)
	Hp *= X1;
    for (int i = 0; i < n; i++) {
	ull sum = 0;
	for (int j = 0; j < y - 1; j++)
	    sum = sum * X1 + a[i][j];
	for (int j = y - 1; j < m; j++) {
	    sum = sum * X1 + a[i][j];
	    H[i][j - y + 1] = sum;
	    sum -= Hp * a[i][j - y + 1];
	}
    }
    int ans = 0;
    Hp = 1;
    for (int i = 0; i < x - 1; i++)
	Hp *= X2;
    for (int j = 0; j < m - y + 1; j++) {
	ull sum = 0;
	for (int i = 0; i < x - 1; i++)
	    sum = sum * X2 + H[i][j];
	for (int i = x - 1; i < n; i++) {
	    sum = sum * X2 + H[i][j];
	    if (sum == u) ans++;
	    sum -= Hp * H[i - x + 1][j];
	}
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	    scanf("%s", a[i]);
	scanf("%d%d", &x, &y);
	for (int i = 0; i < x; i++)
	    scanf("%s", b[i]);
	printf("%d\n", solve());
    }
    return 0;
}

#include <cstdio>
#include <cstring>

typedef unsigned long long ull;

ull X = 123;
const int N = 1005;

int t, n, m, x, y, cnt[N][N];
char str[N];
ull H[N][N], Hp[N], now;

void gao(char *str, ull *H, int *cnt) {
    for (int i = 0; i < m - y + 1; i++) {
	if (now == H[i] - H[i + y] * Hp[y])
	    cnt[i]++;
    }
}

int solve() {
    memset(cnt, 0, sizeof(cnt));
    scanf("%d%d", &x, &y);
    for (int i = 0; i < x; i++) {
	scanf("%s", str);
	now = 0;
	for (int j = y - 1; j >= 0; j--)
	    now = now * X + str[j] - 'a';
	for (int j = i; j < n; j++)
	    gao(str, H[j], cnt[j - i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
	    if (cnt[i][j] == x)
		ans++;
    return ans;
}

int main() {
    Hp[0] = 1;
    for (int i = 1; i < N; i++)
	Hp[i] = Hp[i - 1] * X;
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
	    scanf("%s", str);
	    H[i][m] = 0;
	    for (int j = m - 1; j >= 0; j--)
		H[i][j] = H[i][j + 1] * X + str[j] - 'a';
	}
	printf("%d\n", solve());
    }
    return 0;
}

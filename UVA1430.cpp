#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

typedef long long ll;

const int N = 10005;
const int MOD = 10007;

int n, k, C[45][45], dp[25][45], frc[45];

int pow_MOD(int x, int k, int MOD) {
    int ans = 1;
    while (k) {
	if (k&1) ans = ans * x % MOD;
	x = x * x % MOD;
	k >>= 1;
    }
    return ans;
}

int inv(int a, int n) {
    return pow_MOD(a, n - 2, n);
}

int main() {
    for (int i = 0; i <= 40; i++) {
	if (!i) frc[i] = 1;
	else frc[i] = frc[i - 1] * i % MOD;
	C[i][0] = C[i][i] = 1;
	for (int j = 1; j < i; j++)
	    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    int cas = 0;
    while (~scanf("%d%d", &n, &k) && n || k) {
	char s[55], t[55];
	scanf("%s%s", s, t);
	int cnt = 0;
	for (int i = 0; i < n; i++)
	    if (s[i] != t[i])
		cnt++;
	int tot = n * (n - 1) * (n - 2) / 6;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 1; i <= k; i++) {
	    for (int x = 0; x <= n; x++) {
		if (i != 1)
		    dp[i][x] = ((dp[i][x] - dp[i - 2][x] * (tot - (i - 2))) % MOD + MOD) % MOD;
		int one = dp[i - 1][x] * inv(C[n][x], MOD) % MOD;
		if (n - 3 >= x)
		    dp[i][x + 3] = (dp[i][x + 3] + one * C[n - 3][x] % MOD * tot % MOD) % MOD;
		if (x - 1 >= 0 && n - 3 >= x - 1)
		    dp[i][x + 1] = (dp[i][x + 1] + one * C[n - 3][x - 1] % MOD * 3 % MOD * tot % MOD) % MOD;
		if (x - 2 >= 0 && n - 3 >= x - 2)
		    dp[i][x - 1] = (dp[i][x - 1] + one * C[n - 3][x - 2] % MOD * 3 % MOD * tot % MOD) % MOD;
		if (x - 3 >= 0 && n - 3 >= x - 3)
		    dp[i][x - 3] = (dp[i][x - 3] + one * C[n - 3][x - 3] % MOD * tot % MOD) % MOD;
	    }
	}
	
	   for (int i = 1; i <= k; i++) {
	   for (int j = 0; j <= n; j++)
	   printf("%d %d %d\n", i, j, dp[i][j]);
	   }
	printf("Case #%d: %d\n", ++cas, dp[k][cnt] * inv(frc[k], MOD) % MOD); 
    }
    return 0;
}

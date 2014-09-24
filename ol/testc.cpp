#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int t, a, b;
int bit[15], pow2[15], n;
int dp[11][10000];

void build() {
	n = 0;
	if (b == 0) bit[n++] = 0;
	while (b) {
		bit[n++] = b % 10;
		b /= 10;
	}
}

int dfs(int u, int s, int flag) {
	if (s < 0) return 0;
	if (u == -1)
		return s >= 0;
	int &ans = dp[u][s];
	if (flag && ans != -1) return ans;
	int tmp = 0;
	if (flag) {
		for (int i = 0; i < 10; i++)
			tmp += dfs(u - 1, s -  i * pow2[u], 1);
	} else {
		for (int i = 0; i < bit[u]; i++)
			tmp += dfs(u - 1, s - i * pow2[u], 1);
		tmp += dfs(u - 1, s - bit[u] * pow2[u], 0);
	}
	if (flag) ans = tmp;
	return tmp;
}

int main() {
	int cas = 0;
	pow2[0] = 1;
	for (int i = 1; i < 10; i++)
		pow2[i] = pow2[i - 1] * 2;
	scanf("%d", &t);
	memset(dp, -1, sizeof(dp));
	while (t--) {
		scanf("%d%d", &a, &b);
		int sum = 0;
		int cn = 0;
		while (a) {
			sum += a % 10 * pow2[cn++];
			a /= 10;
		}
		build();
		printf("Case #%d: %d\n", ++cas, dfs(n - 1, sum, 0));
	}
	return 0;
}

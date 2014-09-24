#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lowbit(x) (x&(-x))

const int N = 10005;
const int M = 105;
const int MOD = 123456789;

int n, m, dp[N][M], bit[105][N];

void add(int *bit, int x, int v) {
	while (x < N) {
		bit[x] = (bit[x] + v) % MOD;
		x += lowbit(x);
	}
}

int get(int *bit, int x) {
	int ans = 0;
	while (x) {
		ans = (ans + bit[x]) % MOD;
		x -= lowbit(x);
	}
	return ans;
}

struct Num {
	int val, rank, id;
} num[N];

bool cmpid(Num a, Num b) {
	return a.id < b.id;
}

bool cmpval(Num a, Num b) {
	return a.val < b.val;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		memset(bit, 0, sizeof(bit));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &num[i].val);
			num[i].id = i;
		}
		sort(num + 1, num + n + 1, cmpval);
		num[1].rank = 2;
		for (int i = 2; i <= n; i++) {
			num[i].rank = num[i - 1].rank;
			if (num[i].val > num[i - 1].val)
				num[i].rank++;
		}
		sort(num + 1, num + n + 1, cmpid);
		add(bit[0], 1, 1);
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			for (int j = min(m, i); j >= 1; j--) {
				int tmp = get(bit[j - 1], num[i].rank - 1);
				dp[i][j] = (dp[i][j] + tmp) % MOD;
				add(bit[j], num[i].rank, tmp);
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans = (ans + dp[i][m]) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}

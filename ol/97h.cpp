#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int N = 200005;
typedef unsigned long long ull;
typedef long long ll;

int t, n, q, W[N], T[N], ans[55][N];
ull dp[N];
map<ll, int> LOG;

int main() {
	scanf("%d", &t);
	for (int i = 0; i < 52; i++)
		LOG[(1ULL<<i)] = i;
	while (t--) {
		scanf("%d%d", &n, &q);
		memset(dp, 0, sizeof(dp));
		memset(ans, 0, sizeof(ans));
		dp[0] = 1;
		for (int i = 1; i <= n; i++) { 
			scanf("%d%d", &W[i], &T[i]);
			for (int j = 200000; j >= T[i]; j--) {
				ull tmp = dp[j];
				if (dp[j - T[i]] == 0) continue;
				dp[j] |= ((dp[j - T[i]])<<W[i]) & ((1ULL<<52) - 1);
				for (ull k = (tmp^dp[j]); k > 0; k &= (k - 1)) {
					ll x = k;
					ans[LOG[(x&(-x))]][j] = i;
				}
			}
		}
		int m, s;
		for (int i = 0; i < q; i++) {
			scanf("%d%d", &m, &s);
			if (!ans[m][s]) printf("No solution!\n");
			else {
				int v = ans[m][s];
				int bo = 0;
				while (v) {
					if (bo) printf(" ");
					else bo = 1;
					printf("%d", v);
					m -= W[v];
					s -= T[v];
					v = ans[m][s];
				}
				printf("\n");
			}
		}
	}
	return 0;
}

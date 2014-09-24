#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 105;
const int INF = 0x3f3f3f3f;
int n, m, a[N], Max[N][55][2], Min[N][55][2], num[2];
char str[N];

int main() {
	num[0] = 1;
	num[1] = -1;
	int cas = 0;
	while (~scanf("%d", &n)) {
		scanf("%s%d", str + 1, &m);
		memset(Max, -INF, sizeof(Max));
		memset(Min, INF, sizeof(Min));
		for (int i = 1; i <= n; i++)
			a[i] = str[i] - 'A';
		Max[0][0][0] = 0;
		Min[0][0][0] = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= m; j++) {
				for (int k = 0; k < 2; k++) {
					if (a[i + 1]) {
						Max[i + 1][j][!k] = max(Max[i + 1][j][!k], Max[i][j][k]);
						Max[i + 1][j + 1][k] = max(Max[i + 1][j + 1][k], Max[i][j][k] + num[k]);
						Min[i + 1][j][!k] = min(Min[i + 1][j][!k], Min[i][j][k]);
						Min[i + 1][j + 1][k] = min(Min[i + 1][j + 1][k], Min[i][j][k] + num[k]);
					} else {
						Max[i + 1][j + 1][!k] = max(Max[i + 1][j + 1][!k], Max[i][j][k]);
						Max[i + 1][j][k] = max(Max[i + 1][j][k], Max[i][j][k] + num[k]);
						Min[i + 1][j + 1][!k] = min(Min[i + 1][j + 1][!k], Min[i][j][k]);
						Min[i + 1][j][k] = min(Min[i + 1][j][k], Min[i][j][k] + num[k]);
					}
				}
			}
		}
		int ans1 = INF, ans2 = -INF;
		int st = m % 2;
		for (int i = st; i <= m; i += 2) {
			ans1 = min(ans1, Min[n][i][0]);
			ans1 = min(ans1, Min[n][i][1]);
			ans2 = max(ans2, Max[n][i][0]);
			ans2 = max(ans2, Max[n][i][1]);
		}
		int ans = -INF;
		ans = max(ans2, -ans1);
		printf("Case #%d: %d\n", ++cas, ans);
	}
	return 0;
}

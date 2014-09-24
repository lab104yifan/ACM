#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int d[8][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

const int N = 105;
int n, sum[N][N][10];
char g[N][N];

int dfs(int x, int y, int dd) {
	if (x <= 0 || x > n || y <= 0 || y > n) return 0;
	if (sum[x][y][dd] != -1) return sum[x][y][dd];
	if (g[x][y] == '#') return sum[x][y][dd] = 0;
	sum[x][y][dd] = dfs(x + d[dd][0], y + d[dd][1], dd) + 1;
	return sum[x][y][dd];
}

int main() {
	while (~scanf("%d", &n) && n) {
		memset(sum, -1, sizeof(sum));
		for (int i = 1; i <= n; i++)
			scanf("%s", g[i] + 1);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (g[i][j] == '.') {
					for (int k = 0; k < 8; k++)
						dfs(i, j, k);
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 0; k < 4; k++) {
					if (g[i][j] == '#') continue;
					ans = max(ans, sum[i][j][k] + sum[i][j][(k + 1) % 4] - 1);
					ans = max(ans, sum[i][j][k + 4] + sum[i][j][(k + 1) % 4 + 4] - 1);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

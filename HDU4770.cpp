#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 205;
const int d[4][3][2] = {{{0, 0}, {-1, 0}, {0, 1}},
			{{0, 0}, {1, 0}, {0, 1}},
			{{0, 0}, {1, 0}, {0, -1}},
			{{0, 0}, {-1, 0}, {0, -1}}};

int n, m, g[N][N], x[N], y[N], pn, light[N][N], put[N][N], ans;
char str[N];

bool judge(int x, int y, const int d[][2], int &ans) {
    if (put[x][y]) return false;
    ans = 0;
    for (int i = 0; i < 3; i++) {
	int xx = x + d[i][0];
	int yy = y + d[i][1];
	if (xx > n || xx < 1 || yy > m || yy < 1) continue;
	if (!g[xx][yy]) return false;
    }
    for (int i = 0; i < 3; i++) {
	int xx = x + d[i][0];
	int yy = y + d[i][1];
	if (xx > n || xx < 1 || yy > m || yy < 1) continue;
	if (light[xx][yy] == 0) ans++;
	light[xx][yy]++;
    }
    return true;
}

bool judge2(int now) {
    for (int i = 0; i < pn; i++) {
	if (x[i] <= now) break;
	if (!light[x[i]][y[i]]) return false;
    }
    return true;
}

int dfs(int now, int li, int num) {
    if (num > ans) return INF;
    if (!judge2(x[now])) return INF;
    if (li == 0) return num;
    if (now == pn) return INF;
    int tmp;
    int ans = INF;
    if (judge(x[now], y[now], d[0], tmp)) {
	ans = min(ans, dfs(now + 1, li - tmp, num + 1));
	for (int i = 0; i < 3; i++) {
	    int xx = x[now] + d[0][i][0];
	    int yy = y[now] + d[0][i][1];
	    if (xx > n || xx < 1 || yy > m || yy < 1) continue;
	    light[xx][yy]--;
	}
    }
    ans = min(ans, dfs(now + 1, li, num));
    return ans;
}

int main() {
    while (~scanf("%d%d", &n, &m) && n || m) {
	for (int i = 1; i <= n; i++) {
	    scanf("%s", str + 1);
	    for (int j = 1; j <= m; j++)
		g[i][j] = (str[j] == '.'?1:0);
	}
	pn = 0;
	for (int i = n; i >= 1; i--) {
	    for (int j = 1; j <= m; j++) {
		if (g[i][j]) {
		    x[pn] = i;
		    y[pn] = j;
		    pn++;
		}
	    }
	}
	memset(light, 0, sizeof(light));
	ans = INF;
	ans = dfs(0, pn, 0);
	for (int i = 0; i < pn; i++) {
	    for (int j = 0; j < 4; j++) {
		int tmp = 0;
		memset(light, 0, sizeof(light));
		if (judge(x[i], y[i], d[j], tmp)) {
		    put[x[i]][y[i]] = 1;
		    ans = min(ans, dfs(0, pn - tmp, 1));
		    put[x[i]][y[i]] = 0;
		}
	    }
	}
	if (ans == INF) printf("-1\n");
	else printf("%d\n", ans);
    }
    return 0;
}

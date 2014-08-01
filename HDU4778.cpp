#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 21;
int g, b, s, dp[(1<<N) + 5], vis[(1<<N) + 5];
int yu[(1<<N) + 5][10];

struct Page {
    int num;
    int a[10];
} p[N];

int cal(int S, int u) {
    int ans = 0;
    for (int i = 1; i <= g; i++) {
	ans += (yu[S][i] + p[u].a[i]) / s;
    }
    return ans;
}

int dfs(int now) {
    int &tmp = dp[now];
    if (vis[now]) return tmp;
    vis[now] = 1;
    tmp = 0;
    int Min = INF, Max = -INF;
    if (now == (1<<b) - 1) return tmp;
    for (int i = 0; i < b; i++) {
	if (now&(1<<i)) continue;
	int sb = cal(now, i);
	int next = (now|(1<<i));
	if (sb != 0) {
	    Max = max(Max, dfs(next) + sb);
	}
	else {
	    Min = min(Min, dfs(next));
	}
    }
    tmp = max(Max, -Min);
    return tmp;
}

int main() {
    while (~scanf("%d%d%d", &g, &b, &s) && g || b || s) {
	for (int i = 0; i < b; i++) {
	    memset(p[i].a, 0, sizeof(p[i].a));
	    scanf("%d", &p[i].num);
	    int tmp;
	    for (int j = 0; j < p[i].num; j++) {
		scanf("%d", &tmp);
		p[i].a[tmp]++;
	    }
	}
	for (int i = 0; i < (1<<b); i++) {
	    vis[i] = 0;
	    for (int j = 0; j < b; j++) {
		if (i&(1<<j)) continue;
		for (int k = 1; k <= g; k++) {
		    yu[i|(1<<j)][k] = (yu[i][k] + p[j].a[k]) % s;
		}
	    }
	}
	printf("%d\n", dfs(0));
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 25;
const int M = 55;

int t, n, m;
int g[M][M], save[N][M];

struct Pro {
    int val;
    ll s;
} pro[N];

int vis[M], cost[M], pre[N];

void dfs(int u, int now) {
    vis[u] = 1;
    pro[now].s |= (1LL<<u);
    for (int v = 0; v < m; v++) {
	if (g[u][v] == 0) continue;
	if (vis[v]) continue;
	dfs(v, now);
    }
}

void build(int now) {
    pro[now].s = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= save[now][0]; i++) {
	if (vis[save[now][i]]) continue;
	pro[now].s |= (1LL<<save[now][i]);
	dfs(save[now][i], now);
    }
}

int out;

void dfs1(int now, ll s, int sum) {
    int sb;
    if (now == -1) sb = 0;
    else sb = pre[now];
    if (sum + pre[n - 1] - sb <= out) return;
    int ss = 0;
    for (int i = 0; i < m; i++) {
	if ((1LL<<i)&s) {
	    ss += cost[i]; 
	}
    }
    out = max(sum - ss, out);
    for (int i = now + 1; i < n; i++)
	dfs1(i, (s|pro[i].s), sum + pro[i].val);
}

void init() {
    out = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
	scanf("%d", &pro[i].val);
	if (i) pre[i] = pre[i - 1] + pro[i].val;
	else pre[i] = pro[i].val;
    }
    for (int i = 0; i < m; i++)
	scanf("%d", &cost[i]);
    for (int i = 0; i < n; i++) {
	scanf("%d", &save[i][0]);
	for (int j = 1; j <= save[i][0]; j++)
	    scanf("%d", &save[i][j]);
    }
    memset(g, 0, sizeof(g));
    for (int i = 0; i < m; i++)
	for (int j = 0; j < m; j++) {
	    scanf("%d", &g[i][j]);
	}
    for (int i = 0; i < n; i++)
	build(i);
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	init();
	dfs1(-1, 0, 0);
	printf("Case #%d: %d\n", ++cas, out);
    }
    return 0;
}

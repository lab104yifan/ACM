#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int MAXS = (1<<15);
const int N = 105;
int t, n, m, k[N], sg[N], cnt[MAXS];
vector<int> g[N];

int bitcount(int x) {
    int ans = 0;
    while (x) {
	ans += (x&1);
	x >>= 1;
    }
    return ans;
}

int dfs(int u) {
    if (sg[u] != -1) return sg[u];
    if (g[u].size() == 0) return sg[u] = 0;
    for (int i = 0; i < g[u].size(); i++)
	dfs(g[u][i]);
    int maxs = (1<<g[u].size());
    map<int, int> vis;
    for (int i = 0; i < maxs; i++) {
	if (cnt[i] > k[u]) continue;
	if ((cnt[i]^k[u])&1) continue;
	int x = 0;
	for (int j = 0; j < g[u].size(); j++) {
	    if (i&(1<<j))
		x ^= sg[g[u][j]];
	}
	vis[x] = 1;
    }
    for (int i = 0; ; i++)
	if (!vis.count(i))
	    return sg[u] = i;
}

void getsg() {
    memset(sg, -1, sizeof(sg));
    for (int i = 0; i < n; i++)
	dfs(i);
}

int main() {
    for (int i = 0; i < MAXS; i++)
	cnt[i] = bitcount(i);
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	    g[i].clear();
	int u, v;
	while (m--) {
	    scanf("%d%d", &u, &v);
	    g[u].push_back(v);
	}
	for (int i = 0; i < n; i++)
	    scanf("%d", &k[i]);
	getsg();
	scanf("%d", &m);
	printf("Game#%d:\n", ++cas);
	int rou = 0;
	while (m--) {
	    int sum = 0, x;
	    for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x&1) sum ^= sg[i];
	    }
	    printf("Round#%d: %s\n", ++rou, sum == 0 ? "LOSING" : "WINNING");
	}
	printf("\n");
    }
    return 0;
}

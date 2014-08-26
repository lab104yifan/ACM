#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;
const int N = 100005;
int n, num[N], vis[N], a[N], b[N];
vector<int> g[N];

void init() {
    for (int i = 1; i <= 100000; i++) {
	int m = (int)sqrt(i * 1.0);
	for (int j = 1; j <= m; j++) {
	    if (i % j) continue;
	    g[i].push_back(j);
	    if (i / j != j)
		g[i].push_back(i / j);
	}
    }
}

int main() {
    init();
    while (~scanf("%d", &n) && n) {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++) {
	    scanf("%d", &num[i]);
	    if (!vis[num[i]]) a[i] = num[i];
	    else a[i] = vis[num[i]];
	    for (int j = 0; j < g[num[i]].size(); j++)
		vis[g[num[i]][j]] = num[i];
	}
	memset(vis, 0, sizeof(vis));
	ll ans = 0;
	for (int i = n - 1; i >= 0; i--) {
	    if (!vis[num[i]])
		ans += (ll)a[i] * num[i];
	    else
		ans += (ll)a[i] * vis[num[i]];
	    for (int j = 0; j < g[num[i]].size(); j++)
		vis[g[num[i]][j]] = num[i];
	}
	printf("%I64d\n", ans);
    }
    return 0;
}

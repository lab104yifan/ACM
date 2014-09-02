#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1005;
const int INF = 0x3f3f3f3f;

int pre[N], low[N], dfs_clock;

int n, m;

struct Node {
	int v, val, id;
	Node() {}
	Node(int v, int val, int id) {
		this->v = v;
		this->val = val;
		this->id = id;
	}
};

vector<Node> g[N];
int ans;

int dfs(int u, int fa) {
	int lowu = pre[u] = ++dfs_clock;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		int id = g[u][i].id;
		if (id == fa) continue;
		if (!pre[v]) {
			int lowv = dfs(v, id);
			lowu = min(lowu, lowv);
			if (lowv > pre[u])
				ans = min(ans, g[u][i].val);
		} else lowu = min(lowu, pre[v]);
	}
	return low[u] = lowu;
}

int main() {
	while (~scanf("%d%d", &n, &m) && n) {
		int u, v, val;
		memset(pre, 0, sizeof(pre));
		dfs_clock = 0;
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &val);
			u--; v--;
			g[u].push_back(Node(v, val, i));
			g[v].push_back(Node(u, val, i));
		}
		int cnt = 0;
		ans = INF;
		for (int i = 0; i < n; i++) {
			if (!pre[i]) {
				cnt++;
				dfs(i, -1);
			}
		}
		if (cnt > 1) printf("0\n");
		else if (ans == INF) printf("-1\n");
		else {
			if (ans == 0) ans = 1;
			printf("%d\n", ans);
		}
	}
	return 0;
}

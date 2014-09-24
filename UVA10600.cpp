#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 105;
const int M = 1000005;

int t, n, m;

struct Edge {
	int u, v, val;
	bool ismst;
	void read() {
		scanf("%d%d%d", &u, &v, &val);
		u--; v--;
		ismst = false;
	}
} e[M];

bool cmp(Edge a, Edge b) {
	return a.val < b.val;
}

vector<Edge> g[N];

int parent[N];

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

int Maxcost[N][N];
const int INF = 0x3f3f3f3f;

void dfs(int s, int u, int Max, int fa) {
	Maxcost[s][u] = max(Maxcost[s][u], Max);
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		if (fa == v) continue;
		int tmp = max(Max, g[u][i].val);
		dfs(s, v, tmp, u);
	}
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			g[i].clear();
		}
		for (int i = 0; i < m; i++)
			e[i].read();
		sort(e, e + m, cmp);
		int ans = 0;
		for (int i = 0; i < m; i++) {
			int pu = find(e[i].u);
			int pv = find(e[i].v);
			if (pu != pv) {
				ans += e[i].val;
				parent[pu] = pv;
				e[i].ismst = true;
				g[e[i].u].push_back(e[i]);
				swap(e[i].u, e[i].v);
				g[e[i].u].push_back(e[i]);
			}
		}
		memset(Maxcost, 0, sizeof(Maxcost));
		for (int i = 0; i < n; i++)
			dfs(i, i, 0, -1);
		int ans2 = INF;
		for (int i = 0; i < m; i++) {
			if (e[i].ismst) continue;
			ans2 = min(ans2, ans - Maxcost[e[i].u][e[i].v] + e[i].val);
		}
		printf("%d %d\n", ans, ans2);
	}
	return 0;
}

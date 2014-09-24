#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 5005;

int n, path[N], pn;
vector<int> g[N];

bool dfs(int u, int e, int fa) {
	path[pn++] = u;
	if (u == e) return true;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (fa == v) continue;
		if (dfs(v, e, u)) return true;
	}
	pn--;
	return false;
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			g[i].clear();
		int u, v;
		for (int i = 0; i < n - 1; i++) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int q;
		scanf("%d", &q);
		int s, e;
		while (q--) {
			scanf("%d%d", &s, &e);
			pn = 0;
			dfs(s, e, -1);
			if (pn % 2) printf("The fleas meet at %d.\n", path[pn / 2]);
			else {
				int a = path[pn / 2 - 1], b = path[pn / 2];
				if (a > b) swap(a, b);
				printf("The fleas jump forever between %d and %d.\n", a, b);
			}
		}
	}
	return 0;
}

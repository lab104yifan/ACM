#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int N = 1005;

int n, m, du[N], vis[N];
vector<int> g[N];

void init() {
	memset(du, 0, sizeof(du));
	for (int i = 1; i <= n; i++)
		g[i].clear();
	int u, v;
	while (m--) {
		scanf("%d%d", &u, &v);
		du[u]++; du[v]++;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

bool solve() {
	int st[2], sn = 0;
	for (int i = 1; i <= n; i++) {
		if (du[i] == 1 || du[i] == 0) return false;
		if (du[i] % 2)
			st[sn++] = i;
	}
	if (sn == 0) {
		printf("0\n");
		return true;
	}
	memset(vis, -1, sizeof(vis));
	queue<int> Q;
	Q.push(st[0]);
	vis[st[0]] = 0;
	while (!Q.empty()) {
		int u = Q.front();
		if (u == st[1]) {
			printf("%d\n", vis[u]);
			return true;
		}
		Q.pop();
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (du[v] == 2) continue;
			if (vis[v] != -1) continue;
			vis[v] = vis[u] + 1;
			Q.push(v);
		}
	}
	return false;
}

int main() {
	while (~scanf("%d%d", &n, &m) && n) {
		init();
		if (!solve()) printf("Poor Koorosh\n");
	}
	return 0;
}

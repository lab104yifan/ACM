#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

const int N = 505;

int t, n;

struct People {
	int s, x1, y1, x2, y2;
	void read() {
		int h, m;
		scanf("%d:%d%d%d%d%d", &h, &m, &x1, &y1, &x2, &y2);
		s = h * 60 + m;
	}
	bool operator < (const People& c) const {
		return s < c.s;
	}
} p[N];

vector<int> g[N];

bool judge(People a, People b) {
	int tmp = a.s + abs(a.x2 - a.x1) + abs(a.y2 - a.y1) + abs(a.x2 - b.x1) + abs(a.y2 - b.y1);
	if (tmp < b.s) return true;
	return false;
}

int match[N], vis[N];

bool dfs(int u) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int hungary() {
	int ans = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			g[i].clear();
			p[i].read();
		}
		sort(p, p + n);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				if (judge(p[i], p[j]))
					g[i].push_back(j);
			}
		printf("%d\n", n - hungary());
	}
	return 0;
}

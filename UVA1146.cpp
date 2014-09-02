#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXNODE = 2005;

struct TwoSet {
	int n;
	vector<int> g[MAXNODE * 2];
	bool mark[MAXNODE * 2];
	int S[MAXNODE * 2], sn;

	void init(int tot) {
		n = tot * 2;
		for (int i = 0; i < n; i += 2) {
			g[i].clear();
			g[i^1].clear();
		}
		memset(mark, false, sizeof(mark));
	}

	void add_Edge(int u, int uval, int v, int vval) {
		u = u * 2 + uval;
		v = v * 2 + vval;
		g[u^1].push_back(v);
		g[v^1].push_back(u);
	}

	bool dfs(int u) {
		if (mark[u^1]) return false;
		if (mark[u]) return true;
		mark[u] = true;
		S[sn++] = u;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (!dfs(v)) return false;
		}
		return true;
	}

	bool solve() {
		for (int i = 0; i < n; i += 2) {
			if (!mark[i] && !mark[i + 1]) {
				sn = 0;
				if (!dfs(i)){
					for (int j = 0; j < sn; j++)
						mark[S[j]] = false;
					sn = 0;
					if (!dfs(i + 1)) return false;
				}
			}
		}
		return true;
	}
} gao;

const int N = 2005;

int n, ti[N][2];
int L, R;

bool judge(int len) {
	gao.init(n);
	for (int i = 0; i < n; i++) {
		for (int a = 0; a < 2; a++) {
			for (int j = i + 1; j < n; j++) {
				for (int b = 0; b < 2; b++) {
					if (abs(ti[i][a] - ti[j][b]) < len)
						gao.add_Edge(i, a^1, j, b^1);
				}
			}
		}
	}
	return gao.solve();
}

int main() {
	while (~scanf("%d", &n)) {
		L = R = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 2; j++) {
				scanf("%d", &ti[i][j]);
				R = max(R, ti[i][j]);
			}
		R++;
		while (L < R) {
			int mid = (L + R) / 2;
			if (judge(mid)) L = mid + 1;
			else R = mid;
		}
		printf("%d\n", L - 1);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXNODE = 100005;

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

const int N = 100005;

int n, m, age[N], sum;
vector<int> g[N];

int main() {
	while (~scanf("%d%d", &n, &m) && n) {
		sum = 0;
		gao.init(n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &age[i]);
			g[i].clear();
			sum += age[i];
		}
		for (int i = 0; i < n; i++) {
			if (age[i] * n < sum)
				age[i] = 0;
			else
				age[i] = 1;
		}
		int u, v;
		while (m--) {
			scanf("%d%d", &u, &v);
			u--; v--;
			g[u].push_back(v);
		}
		for (int u = 0; u < n; u++) {
			for (int j = 0; j < g[u].size(); j++) {
				int v = g[u][j];
				if (age[u]^age[v])
					gao.add_Edge(u, 1, v, 1);
				else {
					gao.add_Edge(u, 0, v, 0);
					gao.add_Edge(u, 1, v, 1);
				}
			}
		}
		if (gao.solve()) {
			for (int i = 0; i < n; i++) {
				if (age[i] && gao.mark[i * 2 + 1]) printf("A\n");
				else if (age[i] == 0 && gao.mark[i * 2 + 1]) printf("B\n");
				else printf("C\n");
			}
		} else printf("No solution.\n");
	}
	return 0;
}

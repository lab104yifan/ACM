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

int n, m;

int main() {
	while (~scanf("%d%d", &n, &m) && n || m) {
		gao.init(2 * n);
		for (int i = 0; i < n; i++) {
			gao.add_Edge(i * 2, 0, i * 2 + 1, 0);
			gao.add_Edge(i * 2, 1, i * 2 + 1, 1);
		}
		int u, v;
		char a, b;
		while (m--) {
			scanf("%d%c %d%c", &u, &a, &v, &b);
			u *= 2; v *= 2;
			if (a == 'w') u++;
			if (b == 'w') v++;
			gao.add_Edge(u, 0, v, 0);
		}
		gao.mark[2] = true;
		if (!gao.solve()) printf("bad luck\n");
		else {
			int bo = 0;
			for (int i = 2; i < 2 * n; i++) {
				if (gao.mark[i * 2] == true) {
					if (bo) printf(" ");
					else bo = 1;
					printf("%d%c", i / 2, i % 2 == 0 ? 'h' : 'w');
				}
			}
			printf("\n");
		}
	}
	return 0;
}

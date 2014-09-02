#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXNODE = 105;

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

	void delete_Edge(int u, int uval, int v, int vval) {
		u = u * 2 + uval;
		v = v * 2 + vval;
		g[u^1].pop_back();
		g[v^1].pop_back();
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

const int N = 105;

int n, m;
int a[5];
bool b[5], save[N];

int bitcount(int x) {
	int ans = 0;
	while (x) {
		ans += (x&1);
		x >>= 1;
	}
	return ans;
}

int main() {
	int cas = 0;
	while (~scanf("%d%d", &n, &m) && n || m) {
		int k;
		gao.init(n);

		while (m--) {
			scanf("%d", &k);
			char c;
			for (int i = 0; i < k; i++) {
				scanf("%d %c", &a[i], &c);
				a[i]--;
				if (c == 'y') b[i] = true;
				else b[i] = false;
			}
			if (k <= 2) {
				for (int i = 0; i < k; i++)
					gao.add_Edge(a[i], b[i], a[i], b[i]);
			}
			else {
				for (int i = 0; i < k; i++) {
					for (int j = i + 1; j < k; j++) {
						gao.add_Edge(a[i], b[i], a[j], b[j]);
					}
				}
			}
		}
		printf("Case %d: ", ++cas);
		if (!gao.solve()) printf("impossible\n");
		else {
			for (int i = 0; i < n; i++)
				save[i] = gao.mark[i * 2 + 1];
			for (int i = 0; i < n; i++) {
				memset(gao.mark, false, sizeof(gao.mark));
				gao.add_Edge(i, !save[i], i, !save[i]);
				if (gao.solve()) printf("?");
				else printf("%c", save[i] ? 'y' : 'n');
				gao.delete_Edge(i, !save[i], i, !save[i]);
			}
			printf("\n");
		}
	}
	return 0;
}

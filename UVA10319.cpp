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

int n, S, A, m;

int main() {
	scanf("%d", &n);
	while (n--) {
		scanf("%d%d%d", &S, &A, &m);
		gao.init(S + A);
		int s1, a1, s2, a2;
		while (m--) {
			scanf("%d%d%d%d", &s1, &a1, &s2, &a2);
			s1--; a1--; s2--; a2--;
			if (s1 == s2 && a1 == a2) continue;
			a1 += S;
			a2 += S;
			if (s1 == s2) gao.add_Edge(s1, (a1 < a2), s2, (a1 < a2));
			else if (a1 == a2) gao.add_Edge(a1, (s1 < s2), a2, (s1 < s2));
			else {
				gao.add_Edge(s1, (a1 < a2), s2, (a1 < a2));
				gao.add_Edge(s1, (a1 < a2), a1, (s1 < s2));
				gao.add_Edge(a2, (s1 < s2), s2, (a1 < a2));
				gao.add_Edge(a2, (s1 < s2), a1, (s1 < s2));
			}
		}
		printf("%s\n", gao.solve() ? "Yes" : "No");
	}
	return 0;
}

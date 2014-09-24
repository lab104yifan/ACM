#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXNODE = 505;

typedef int Type;
const Type INF = 0x3f3f3f3f;

struct KM {
	int n;
	Type g[MAXNODE][MAXNODE];
	Type Lx[MAXNODE], Ly[MAXNODE], slack[MAXNODE];
	int left[MAXNODE];
	bool S[MAXNODE], T[MAXNODE];

	void init(int n) {
		this->n = n;
	}

	void add_Edge(int u, int v, Type val) {
		g[u][v] = val;
	}

	bool dfs(int i) {
		S[i] = true;
		for (int j = 0; j < n; j++) {
			if (T[j]) continue;
			Type tmp = Lx[i] + Ly[j] - g[i][j];
			if (!tmp) {
				T[j] = true;
				if (left[j] == -1 || dfs(left[j])) {
					left[j] = i;
					return true;
				}
			} else slack[j] = min(slack[j], tmp);
		}
		return false;
	}

	void update() {
		Type a = INF;
		for (int i = 0; i < n; i++)
			if (!T[i]) a = min(a, slack[i]);
		for (int i = 0; i < n; i++) {
			if (S[i]) Lx[i] -= a;
			if (T[i]) Ly[i] += a;
		}
	}

	void km() {
		for (int i = 0; i < n; i++) {
			left[i] = -1;
			Lx[i] = -INF; Ly[i] = 0;
			for (int j = 0; j < n; j++)
				Lx[i] = max(Lx[i], g[i][j]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) slack[j] = INF;
			while (1) {
				for (int j = 0; j < n; j++) S[j] = T[j] = false;
				if (dfs(i)) break;
				else update();
			}
		}
	}
} gao;

int n;

int main() {
	while (~scanf("%d", &n)) {
		gao.init(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				scanf("%d", &gao.g[i][j]);
			}
		gao.km();
		int ans = 0;
		for (int i = 0; i < n; i++) {
			printf("%d%c", gao.Lx[i], i == n - 1 ? '\n' : ' ');
			ans += gao.Lx[i];
		}
		for (int i = 0; i < n; i++) {
			printf("%d%c", gao.Ly[i], i == n - 1 ? '\n' : ' ');
			ans += gao.Ly[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}

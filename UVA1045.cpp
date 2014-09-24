#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXNODE = 105;

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

	Type km() {
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
		Type ans = 0;
		for (int i = 0; i < n; i++)
			ans += g[left[i]][i];
		return ans;
	}
} gao;

const int N = 20;

int n, x[N], y[N];

int dis(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
	int cas = 0;
	while (~scanf("%d", &n) && n) {
		gao.init(n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &x[i], &y[i]);
			x[i]--; y[i]--;
		}
		int ans = -1000;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					gao.add_Edge(j, k, -dis(x[j], y[j], i, k));
				}
			}
			ans = max(ans, gao.km());
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					gao.add_Edge(j, k, -dis(x[j], y[j], k, i));
				}
			}
			ans = max(ans, gao.km());
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				gao.add_Edge(i, j, -dis(x[i], y[i], j, j));
		ans = max(ans, gao.km());
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				gao.add_Edge(i, j, -dis(x[i], y[i], n - j - 1, j));
		ans = max(ans, gao.km());
		printf("Board %d: %d moves required.\n\n", ++cas, -ans);
	}
	return 0;
}

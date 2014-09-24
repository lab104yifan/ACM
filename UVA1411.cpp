#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXNODE = 105;

typedef double Type;
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
			double tmp = Lx[i] + Ly[j] - g[i][j];
			if (fabs(tmp) < 1e-9) {
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
		double a = INF;
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

const int N = 105;
int n;
struct Point {
	double x, y;
	void read() {
		scanf("%lf%lf", &x, &y);
	}
} a[N], b[N];

double dis(Point a, Point b) {
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

int main() {
	int bo = 0;
	while (~scanf("%d", &n)) {
		if (bo) printf("\n");
		else bo = 1;
		gao.init(n);
		for (int i = 0; i < n; i++)
			a[i].read();
		for (int i = 0; i < n; i++)
			b[i].read();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				gao.add_Edge(i, j, -dis(b[i], a[j]));
		gao.km();
		for (int i = 0; i < n; i++)
			printf("%d\n", gao.left[i] + 1);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1005;

int t, n, parent[N];

struct City {
	int x, y, p;
	void read() {
		scanf("%d%d%d", &x, &y, &p);
	}
} c[N];

struct Edge {
	int u, v;
	double val;
	Edge() {}
	Edge(int u, int v, double val) {
		this->u = u;
		this->v = v;
		this->val = val;
	}
} e[N * N];

int en;

double dis(City a, City b) {
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	return sqrt(dx * dx * 1.0 + dy * dy);
}

bool cmp(Edge a, Edge b) {
	return a.val < b.val;
}

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

vector<Edge> g[N];

double Maxcost[N][N];

void dfs(int s, int u, double Max, int fa) {
	Maxcost[s][u] = max(Maxcost[s][u], Max);
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		if (v == fa) continue;
		double tmp = max(Max, g[u][i].val);
		dfs(s, v, tmp, u);
	}
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			c[i].read();
			parent[i] = i;
			g[i].clear();
		}
		en = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				e[en++] = Edge(i, j, dis(c[i], c[j]));
		sort(e, e + en, cmp);
		double sum = 0;
		for (int i = 0; i < en; i++) {
			int pu = find(e[i].u);
			int pv = find(e[i].v);
			if (pu != pv) {
				parent[pu] = pv;
				sum += e[i].val;
				g[e[i].u].push_back(e[i]);
				swap(e[i].u, e[i].v);
				g[e[i].u].push_back(e[i]);
			}
		}
		memset(Maxcost, 0, sizeof(Maxcost));
		for (int i = 0; i < n; i++)
			dfs(i, i, 0, -1);
		double ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				ans = max((c[i].p + c[j].p) * 1.0 / (sum - Maxcost[i][j]), ans);
			}
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}

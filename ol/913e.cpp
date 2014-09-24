#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10005;
const int M = 40005;
const double eps = 1e-8;

int t, en;

struct Edge {
	int u, v;
	Edge(int u = 0, int v = 0) {
		this->u = u;
		this->v = v;
	}
} E[M];

int n, m, s, e, id[N], idx;
vector<int> g[N];
int parent[N];

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

void dfs(int u) {
	id[u] = idx;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (id[v] != -1) continue;
		dfs(v);
	}
}

double A[1005][1005];

void gauss(int n, int s, int e) {
	if (find(s) != find(e)) {
		printf("inf\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		int r;
		for (r = i; r < n; r++)
			if (fabs(A[r][i]) >= eps)
				break;
		if (r == n) continue;
		for (int j = 0; j <= n; j++) swap(A[i][j], A[r][j]);
		for (int j = n; j > i; j--) A[i][j] /= A[i][i];
		A[i][i] = 1;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (fabs(A[j][i]) >= eps) {
				for (int k = n; k > i; k--)
					A[j][k] -= A[j][i] * A[i][k];
				A[j][i] = 0;
			}
		}
	}
	printf("%.6lf\n", A[s][n] / A[s][s] - A[e][n] / A[e][e]);
}

int main() {
	scanf("%d", &t);
	while (t--) {
		memset(id, -1, sizeof(id));
		en = 0;
		scanf("%d%d%d%d", &n, &m, &s, &e);
		int u, v, r;
		for (int i = 0; i <= n; i++) {
			parent[i] = i;
			g[i].clear();
		}
		while (m--) {
			scanf("%d%d%d", &u, &v, &r);
			if (r == 0) {
				g[u].push_back(v);
				g[v].push_back(u);
			} else
				E[en++] = Edge(u, v);
		}
		idx = 0;
		for (int i = 1; i <= n; i++) {
			if (id[i] != -1) continue;
			dfs(i);
			idx++;
		}
		if (id[s] == id[e]) {
			printf("0.000000\n");
			continue;
		}
		memset(A, 0, sizeof(A));
		idx++;
		A[id[s]][idx] = 1;
		A[id[e]][idx] = -1;
		A[idx - 1][0] = 1;
		for (int i = 0; i < en; i++) {
			int u = id[E[i].u];
			int v = id[E[i].v];
			if (u == v) continue;
			int pu = find(u);
			int pv = find(v);
			if (pu != pv) parent[pu] = pv;
			A[u][u] += 1;
			A[v][v] += 1;
			A[u][v] -= 1;
			A[v][u] -= 1;
		}
		gauss(idx, id[s], id[e]);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 205;
const int M = 1005;

int n, m, parent[N];

struct Edge {
	int u, v, val;
	bool operator < (const Edge& c) const {
		return val < c.val;
	}
	void read() {
		scanf("%d%d%d", &u, &v, &val);
	}
} E[M];

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

int solve(int s, int e) {
	int ans = 1000000000;
	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= n; j++) parent[j] = j;
		for (int j = i; j < m; j++) {
			int pu = find(E[j].u);
			int pv = find(E[j].v);
			if (pu != pv) parent[pu] = pv;
			if (find(s) == find(e)) {
				ans = min(ans, E[j].val - E[i].val);
				break;
			}
		}
	}
	return ans;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < m; i++)
			E[i].read();
		sort(E, E + m);
		int a, b, q, u, v;
		scanf("%d%d", &a, &b);
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d", &u, &v);
			printf("%d\n", a + b + solve(u, v));
		}
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000005;

int t, n, m, parent[N];

struct Block {
	int id, h;
} d[N];

int q[N], vis[N], out[N], on;

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

void merge(int u, int v) {
	int pa = find(u);
	int pb = find(v);
	if (pa != pb) parent[pb] = pb;
}

bool cmp(Block a, Block b) {
	return a.h > b.h;
}

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		d[0].h = d[n + 1].h = -1;
		vis[0] = vis[n + 1] = 0;
		for (int i = 1; i <= n; i++) {
			vis[i] = 0;
			parent[i] = i;
			scanf("%d", &d[i].h);
			d[i].id = i;
		}
		sort(d + 1, d + n + 1, cmp);
		for (int i = 0; i < m; i++)
			scanf("%d", &q[i]);
		int l = 1;
		int ans = 0;
		on = 0;
		printf("Case #%d:", ++cas);
		for (int i = m - 1; i >= 0; i--) {
			while (l <= n && q[i] < d[l].h) {
				if (vis[d[l].id - 1] && vis[d[l].id + 1]) {
					merge(d[l].id, d[l].id - 1);
					merge(d[l].id, d[l].id + 1);
					ans--;
				}
				else if (vis[d[l].id - 1])
					merge(d[l].id, d[l].id - 1);
				else if (vis[d[l].id + 1])
					merge(d[l].id, d[l].id + 1);
				else ans++;
				vis[d[l].id] = 1;
				l++;
			}
			out[on++] = ans;
		}
		for (int i = on - 1; i >= 0; i--)
			printf(" %d", out[i]);
		printf("\n");
	}
	return 0;
}

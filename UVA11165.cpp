#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100005;

int t, n, m, parent[N], vis[N];

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

struct Ban {
	int v1, v2;
	Ban(int v1, int v2) {
		this->v1 = v1;
		this->v2 = v2;
	}
};

bool cmp(Ban a, Ban b) {
	return a.v1 < b.v1;
}

vector<Ban> b[N];

const int INF = 0x3f3f3f3f;

int bfs(int s, int t) {
	queue<int> Q;
	Q.push(s);
	vis[s] = 0;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if (u == t) return vis[u];
		int v = find(0);
		int s = 0;
		while (v < n) {
			if (v == u) v = find(v + 1);
			else {
				int flag = 1;
				for (int i = s; i < b[u].size(); i++) {
					if (b[u][i].v1 <= v && b[u][i].v2 >= v) {
						flag = 0;
						v = find(b[u][i].v2 + 1);
						s = i + 1;
						break;
					}
				}
				if (flag) {
					vis[v] = vis[u] + 1;
					Q.push(v);
					parent[v] = find(v + 1);
					v = find(v);
				}
			}
		}
	}
	return -1;
}

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= n; i++) {
			parent[i] = i;
			b[i].clear();
		}
		int u, v1, v2;
		while (m--) {
			scanf("%d%d-%d", &u, &v1, &v2);
			if (v1 > v2) swap(v1, v2);
			b[u].push_back(Ban(v1, v2));
		}
		for (int i = 0; i < n; i++)
			sort(b[i].begin(), b[i].end(), cmp);
		int s, t;
		scanf("%d%d", &s, &t);
		printf("Case #%d: ", ++cas);
		int tmp = bfs(s, t);
		if (tmp == -1) printf("Impossible\n");
		else printf("%d\n", tmp);
	}
	return 0;
}

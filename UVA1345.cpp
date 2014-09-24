#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <set>
using namespace std;

const int MAXNODE = 1505;
const int MAXEDGE = 1100005;

typedef int Type;
const Type INF = 0x3f3f3f3f;

struct Edge {
	int u, v;
	Type cap, flow;
	Edge() {}
	Edge(int u, int v, Type cap, Type flow) {
		this->u = u;
		this->v = v;
		this->cap = cap;
		this->flow = flow;
	}
};

struct Dinic {
	int n, m, s, t;
	Edge edges[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	bool vis[MAXNODE];
	Type d[MAXNODE];
	int cur[MAXNODE];
	vector<int> cut;

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}
	void add_Edge(int u, int v, Type cap) {
		edges[m] = Edge(u, v, cap, 0);
		next[m] = first[u];
		first[u] = m++;
		edges[m] = Edge(v, u, 0, 0);
		next[m] = first[v];
		first[v] = m++;
	}

	bool bfs() {
		memset(vis, false, sizeof(vis));
		queue<int> Q;
		Q.push(s);
		d[s] = 0;
		vis[s] = true;
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (!vis[e.v] && e.cap > e.flow) {
					vis[e.v] = true;
					d[e.v] = d[u] + 1;
					Q.push(e.v);
				}
			}
		}
		return vis[t];
	}

	Type dfs(int u, Type a) {
		if (u == t || a == 0) return a;
		Type flow = 0, f;
		for (int &i = cur[u]; i != -1; i = next[i]) {
			Edge& e = edges[i];
			if (d[u] + 1 == d[e.v] && (f = dfs(e.v, min(a, e.cap - e.flow))) > 0) {
				e.flow += f;
				edges[i^1].flow -= f;
				flow += f;
				a -= f;
				if (a == 0) break;
			}
		}
		return flow;
	}

	bool Maxflow(int s, int t, int tot) {
		this->s = s; this->t = t;
		Type flow = 0;
		while (bfs()) {
			for (int i = 0; i < n; i++)
				cur[i] = first[i];
			flow += dfs(s, INF);
		}
		return flow == tot;
	}

	void MinCut() {
		cut.clear();
		for (int i = 0; i < m; i += 2) {
			if (vis[edges[i].u] && !vis[edges[i].v])
				cut.push_back(i);
		}
	}
} gao;

const int N = 1005;
const int M = 505;

int n, m, cnt[M];
vector<int> f[N];
char str[100005];

bool judge(int c) {
	gao.init(n + m + 2);
	int s = 0, t = n + m + 1;
	for (int i = 0; i < n; i++) {
		gao.add_Edge(0, i + 1, 1);
		for (int j = 0; j < f[i].size(); j++) {
			gao.add_Edge(i + 1, f[i][j] + n + 1, 1);
		}
	}
	for (int i = 0; i < m; i++)
		gao.add_Edge(n + i + 1, t, c);
	return gao.Maxflow(s, t, n);
}

int main() {
	while (~scanf("%d%d", &n, &m) && n || m) {
		memset(cnt, 0, sizeof(cnt));
		while ((getchar()) != '\n');
		for (int i = 0; i < n; i++) {
			f[i].clear();
			gets(str);
			int len = strlen(str);
			int sum = 0;
			int flag = 0;
			for (int j = 0; j < len; j++) {
				if (str[j] >= '0' && str[j] <= '9') {
					flag = 1;
					sum = sum * 10 + str[j] - '0';
				} else {
					if (flag) {
						f[i].push_back(sum);
						cnt[sum]++;
					}
					flag = 0;
					sum = 0;
				}
			}
			if (flag) {
				f[i].push_back(sum);
				cnt[sum]++;
			}
		}
		int l = 0, r = 0;
		for (int i = 0; i < m; i++) r = max(r, cnt[i]);
		while (l < r) {
			int mid = (l + r) / 2;
			if (judge(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}
	return 0;
}

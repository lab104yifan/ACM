#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 10005;

struct Edge {
	int u, v;
	Edge() {}
	Edge(int u, int v) {
		this->u = u;
		this->v = v;
	}
};

int pre[N], bccno[N], dfs_clock, bcc_cnt;
bool iscut[N];

vector<int> g[N], bcc[N];
stack<Edge> S;

int dfs_bcc(int u, int fa) {
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		Edge e = Edge(u, v);
		if (!pre[v]) {
			S.push(e);
			child++;
			int lowv = dfs_bcc(v, u);
			lowu = min(lowu, lowv);
			if (lowv >= pre[u]) {
				iscut[u] = true;
				bcc_cnt++; bcc[bcc_cnt].clear(); //start from 1
				while(1) {
					Edge x = S.top(); S.pop();
					if (bccno[x.u] != bcc_cnt) {bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt;}
					if (bccno[x.v] != bcc_cnt) {bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt;}
					if (x.u == u && x.v == v) break;
				}
			}
		} else if (pre[v] < pre[u] && v != fa) {
			S.push(e);
			lowu = min(lowu, pre[v]);
		}
	}
	if (fa < 0 && child == 1) iscut[u] = false;
	return lowu;
}

void find_bcc(int n) {
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	dfs_clock = bcc_cnt = 0;
	for (int i = 0; i < n; i++)
		if (!pre[i]) dfs_bcc(i, -1);
}

int n, m;
struct Node {
	int val, id;
	bool operator < (const Node& c) const {
		if (val != c.val)
			return val > c.val;
		return id < c.id;
	}
} node[N];

int main() {
	while (~scanf("%d%d", &n, &m) && n) {
		int u, v;
		for (int i = 0; i < n; i++) {
			g[i].clear();
			node[i].val = 0;
			node[i].id = i;
		}
		while (scanf("%d%d", &u, &v)) {
			if (u == -1 && v == -1)
				break;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		find_bcc(n);
		for (int i = 1; i <= bcc_cnt; i++) {
			for (int j = 0; j < bcc[i].size(); j++) {
				int u = bcc[i][j];
				if (iscut[u])
					node[u].val++;
			}
		}
		sort(node, node + n);
		for (int i = 0; i < m; i++) {
			if (node[i].val == 0) node[i].val = 1;
			printf("%d %d\n", node[i].id, node[i].val);
		}
		printf("\n");
	}
	return 0;
}

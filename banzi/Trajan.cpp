#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

const int N = 1005;

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

int color[N];

bool bipartite(int u, int b) { //b = bccno's bcc
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i]; if (bccno[v] != b) continue;
		if (color[v] == color[u]) return false;
		if (!color[v]) {
			color[v] = 3 - color[u];
			if (!bipartite(v, b)) return false;
		}
	}
	return true;
}

int main() {
	return 0;
}

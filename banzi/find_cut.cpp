#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1005;

struct Edge {
	int u, v, id;
	int fan;
	bool iscut, used;
	Edge() {}
	Edge(int u, int v, int id, int fan) {
		this->u = u;
		this->v = v;
		this->id = id;
		this->fan = fan;
		used = false;
		iscut = false;
	}
};

int pre[N], low[N], dfs_clock;

vector<Edge> g[N];
vector<Edge> cut;

int dfs(int u, int fa) {
	int lowu = pre[u] = ++dfs_clock;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].v;
		int id = g[u][i].id;
		if (id == fa) continue;
		if (!pre[v]) {
			int lowv = dfs(v, id);
			lowu = min(lowu, lowv);
			if (lowv > pre[u]) {
				cut.push_back(g[u][i]);
				g[u][i].iscut = true;
				g[v][g[u][i].fan].iscut = true;
			}
		} else lowu = min(lowu, pre[v]);
	}
	return low[u] = lowu;
}

int bcc_cnt, bccno[N];

void dfs2(int u, int bcc_cnt) {
	bccno[u] = bcc_cnt;
	for (int i = 0; i < g[u].size(); i++) {
		if (g[u][i].iscut) continue;
		int v = g[u][i].v;
		if (bccno[u] == bccno[v]) continue;
		dfs2(v, bcc_cnt);
	}
}

void find_cut(int n) {
	cut.clear();
	memset(pre, 0, sizeof(pre));
	dfs_clock = 0;
	for (int i = 0; i < n; i++) {
		if (!pre[i]) {
			dfs(i, 0);
		}
	}
}

void find_bcc(int n) {
	find_cut(n);
	bcc_cnt = 0;
	memset(bccno, 0, sizeof(bccno));
	for (int i = 0; i < n; i++) {
		if (bccno[i]) continue;
		dfs2(i, ++bcc_cnt);
	}
}

int main() {

	return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <map>
using namespace std;

const int N = 50005;

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

int st;

void find_bcc() {
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	dfs_clock = bcc_cnt = 0;
	dfs_bcc(0, -1);
}

int n, m;

typedef long long ll;

void solve() {
	ll ans1 = 0, ans2 = 1;
	for (int i = 1; i <= bcc_cnt; i++) {
		int cut_cnt = 0;
		for (int j = 0; j < bcc[i].size(); j++)
			if (iscut[bcc[i][j]]) cut_cnt++;
		if (cut_cnt == 1) {
			ans1++; 
			ans2 *= (ll)(bcc[i].size() - cut_cnt);
		}
	}
	if (bcc_cnt == 1) {
		ans1 = 2; 
		ans2 = (ll)bcc[1].size() * (bcc[1].size() - 1) / 2;
	}
	printf(" %lld %lld\n", ans1, ans2);
}

int main() {
	int cas = 0;
	while (~scanf("%d", &m) && m) {
		int u, v, Max = 0;
		while (m--) {
			scanf("%d%d", &u, &v);
			u--; v--;
			g[u].push_back(v);
			g[v].push_back(u);
			Max = max(Max, u);
			Max = max(Max, v);
		}
		find_bcc();
		printf("Case %d:", ++cas);
		solve();
		for (int i = 0; i <= Max; i++)
			g[i].clear();
	}
	return 0;
}

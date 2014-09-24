#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int N = 50005;

int n, vis[N];
vector<int> save;

struct Point {
	int val, id, rank;
} p[N];

bool cmpv(Point a, Point b) {
	return a.val < b.val;
}

bool cmpid(Point a, Point b) {
	return a.id < b.id;
}

const int INF = 0x3f3f3f3f;

int dp[N];

struct State {
	int val, v;
	State() {}
	State(int val, int v) {
		this->val = val;
		this->v = v;
	}
	bool operator < (const State& c) const {
		return val > c.val;
	}
};

int solve() {
	memset(dp, INF, sizeof(dp));
	dp[0] = 0;
	dp[n] = n + 1;
	
	int savev = -1;
	priority_queue<State> Q;
	Q.push(State(0, 0));

	while (!Q.empty()) {
		State u = Q.top();
		//printf("%d %d\n", u.v, u.val);
		if (u.v == n) return u.val;
		Q.pop();
		if (u.v > savev) continue;
		if (u.val > dp[u.v]) continue;
		int cnt = 0;
		save.clear();
		savev = max(savev, u.v);
		for (int i = u.v + 1; i <= n; i++) {
			if (vis[p[i].rank] == 0) {
				cnt++;
				vis[p[i].rank] = 1;
				save.push_back(p[i].rank);
			}
			//printf("%d %d!!\n", i, cnt);
			if (dp[u.v] + cnt * cnt > n) break;
			if (dp[i] > dp[u.v] + cnt * cnt) {
				dp[i] = dp[u.v] + cnt * cnt;
				Q.push(State(dp[i], i));
			}
		}
		for (int i = 0; i < save.size(); i++)
			vis[save[i]] = 0;
	}
	return -1;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &p[i].val);
		int pn = 1;
		for (int i = 2; i <= n; i++) {
			if (p[i].val != p[i - 1].val)
				p[++pn] = p[i];
		}
		n = pn;
		for (int i = 1; i <= n; i++)
			p[i].id = i;
		sort(p + 1, p + n + 1, cmpv);
		p[1].rank = 0;
		int s = 0;
		for (int i = 2; i <= n; i++) {
			if (p[i].val != p[i - 1].val)
				++s;
			p[i].rank = s;
		}
		sort(p + 1, p + n + 1, cmpid);
		printf("%d\n", solve());
	}
	return 0;
}

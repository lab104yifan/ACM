#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 205;

int s, n, m, vis[N][N];

struct State {
	int a, b, val;
	State() {}
	State(int a, int b, int val) {
		this->a = a;
		this->b = b;
		this->val = val;
	}
};

void add(int a, int b, int val, queue<State> &Q) {
	if (vis[a][b] > val) {
		vis[a][b] = val;
		Q.push(State(a, b, val));
	}
}

const int INF = 0x3f3f3f3f;

void solve() {
	memset(vis, INF, sizeof(vis));
	queue<State> Q;
	Q.push(State(0, 0, 0));
	vis[0][0] = 0;
	while (!Q.empty()) {
		State u = Q.front();
		Q.pop();
		int us = s - u.a - u.b;
		int ns, na, nb, val;
		ns = max(0, us - (n - u.a));
		val = u.val + us - ns;
		na = us - ns + u.a;
		nb = u.b;
		add(na, nb, val, Q);
		ns = max(0, us - (m - u.b));
		val = u.val + us - ns;
		na = u.a;
		nb = us - ns + u.b;
		add(na, nb, val, Q);
		na = max(0, u.a - (m - u.b));
		val = u.val + u.a - na;
		nb = u.a - na + u.b;
		add(na, nb, val, Q);
		na = max(0, u.a - (s - us));
		val = u.val + u.a - na;
		nb = u.b;
		add(na, nb, val, Q);
		nb = max(0, u.b - (s - us));
		val = u.val + u.b - nb;
		na = u.a;
		add(na, nb, val, Q);
		nb = max(0, u.b - (n - u.a));
		val = u.val + u.b - nb;
		na = u.b - nb + u.a;
		add(na, nb, val, Q);
	}
}

int t, d;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d%d", &n, &m, &s, &d);
		solve();
		int i;
		int ans;
		for (i = d; i >= 0; i--) {
			ans = INF;
			for (int j = 0; j <= s - i; j++) {
				int k = s - i - j;
				ans = min(ans, vis[i][j]);
				ans = min(ans, vis[i][k]);
				ans = min(ans, vis[j][k]);
				ans = min(ans, vis[j][i]);
				ans = min(ans, vis[k][i]);
				ans = min(ans, vis[k][j]);
			}
			if (ans != INF) break;
		}
		printf("%d %d\n", ans, i);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

typedef unsigned long long ll;

int t;

int tmpg[10][10];

ll rotate(ll x) {
	for (int i = 7; i >= 0; i--) {
		for (int j = 7; j >= 0; j--) {
			if (x % 2) tmpg[i][j] = 1;
			else tmpg[i][j] = 0;
			x /= 2;
		}
	}
	ll ans = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			ans = ans * 2 + tmpg[7 - j][i];
		}
	}
	return ans;
}

struct Puzz {
	ll s[4];
	void init(char str[][10]) {
		s[0] = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				s[0] = s[0] * 2;
				if (str[i][j] == '#')
					s[0]++;
			}
		}
		for (int i = 1; i < 4; i++)
			s[i] = rotate(s[i - 1]);
	}
} sp[10], ep[10];

char str[3][3][10][10];

struct State {
	int u[10];
	int h;
	State() {memset(u, 0, sizeof(u)); h = 0;}
	void hash() {
		int ans = 0;
		for (int i = 0; i < 9; i++)
			ans = ans * 4 + u[i];
		h = ans;
	}
};

int chi[9][4];

set<int> save;

void dfs2(int u, int hash) {
	if (u == 9) {
		save.insert(hash);
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (sp[u].s[i] == ep[u].s[0])
			dfs2(u + 1, hash * 4 + i);
	}
}

void build_set() {
	save.clear();
	dfs2(0, 0);
}

void init() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 3; k++) {
				scanf("%s", str[i][k][j]);
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sp[i * 3 + j].init(str[i][j]);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 3; k++) {
				scanf("%s", str[i][k][j]);
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ep[i * 3 + j].init(str[i][j]);
		}
	}

	build_set();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%d", &chi[i][j]);
		}
	}
}

const int INF = 0x3f3f3f3f;
int vis[300005];
const int d[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

State v, v2;
int vv[10];
int to[4];

bool dfs(int now, int rot) {
	vv[now] = 1;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		int x = now / 3 + d[i][0];
		int y = now % 3 + d[i][1];
		if (x < 0 || x >= 3 || y < 0 || y >= 3) continue;
		int next = x * 3 + y;
		if (vv[next]) continue;
		int uu = (i - v.u[now] + 4) % 4;
		if (chi[now][uu] == 0 || chi[next][(to[i] - v.u[next] + 4) % 4] == 0) continue;
		dfs(next, !rot);
		flag = true;
	}
	if (rot == 0) {
		v.u[now] = (v.u[now] + 1) % 4;
		v2.u[now] = (v2.u[now] + 3) % 4;
	}
	else {
		v.u[now] = (v.u[now] + 3) % 4;
		v2.u[now] = (v2.u[now] + 1) % 4;
	}
	return flag;
}

int bfs() {
	if (save.size() == 0) return -1;
	queue<State> Q;
	memset(vis, INF, sizeof(vis));
	State s;
	Q.push(s);
	vis[s.h] = 0;
	while (!Q.empty()) {
		State u = Q.front();
		if (save.find(u.h) != save.end())
			return vis[u.h];
		Q.pop();
		for (int j = 0; j < 9; j++) {
			memset(vv, 0, sizeof(vv));
			v = u;
			v2 = u;
			bool tmp = dfs(j, 0);
			v.hash(); v2.hash();
			if (vis[v.h] > vis[u.h] + 1) {
				vis[v.h] = vis[u.h] + 1;
				Q.push(v);
			}
			if (tmp && vis[v2.h] > vis[u.h] + 1) {
				vis[v2.h] = vis[u.h] + 1;
				Q.push(v2);
			}
		}
	}
	return -1;
}

int main() {
	to[3] = 1; to[1] = 3;
	to[2] = 0; to[0] = 2;
	scanf("%d", &t);
	while (t--) {
		init();
		printf("%d\n", bfs());
	}
	return 0;
}

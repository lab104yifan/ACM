#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXNODE = 1005;

struct TwoSet {
	int n;
	vector<int> g[MAXNODE * 2];
	bool mark[MAXNODE * 2];
	int S[MAXNODE * 2], sn;

	void init(int tot) {
		n = tot * 2;
		for (int i = 0; i < n; i += 2) {
			g[i].clear();
			g[i^1].clear();
		}
		memset(mark, false, sizeof(mark));
	}

	void add_Edge(int u, int uval, int v, int vval) {
		u = u * 2 + uval;
		v = v * 2 + vval;
		g[u^1].push_back(v);
		g[v^1].push_back(u);
	}

	void delete_Edge(int u, int uval, int v, int vval) {
		u = u * 2 + uval;
		v = v * 2 + vval;
		g[u^1].pop_back();
		g[v^1].pop_back();
	}

	bool dfs(int u) {
		if (mark[u^1]) return false;
		if (mark[u]) return true;
		mark[u] = true;
		S[sn++] = u;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (!dfs(v)) return false;
		}
		return true;
	}

	bool solve() {
		for (int i = 0; i < n; i += 2) {
			if (!mark[i] && !mark[i + 1]) {
				sn = 0;
				if (!dfs(i)){
					for (int j = 0; j < sn; j++)
						mark[S[j]] = false;
					sn = 0;
					if (!dfs(i + 1)) return false;
				}
			}
		}
		return true;
	}
} gao;

typedef long long ll;

struct Point {
	ll x, y;
	Point() {}
	Point(ll x, ll y) {
		this->x = x;
		this->y = y;
	}
	void read() {
		scanf("%lld%lld", &x, &y);
	}
};

int xmul(Point a, Point b, Point c) {
	ll ans = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (ans == 0) return 0;
	if (ans > 0) return 1;
	return -1;
}

bool judge(Point a1, Point b1, Point a2, Point b2) {
	if (min(a1.x, b1.x) <= max(a2.x, b2.x) &&
		min(a1.y, b1.y) <= max(a2.y, b2.y) &&
		min(a2.x, b2.x) <= max(a1.x, b1.x) &&
		min(a2.y, b2.y) <= max(a1.y, b1.y) && 
		xmul(a1, a2, b1) * xmul(a1, b2, b1) <= 0 &&
		xmul(a2, a1, b2) * xmul(a2, b1, b2) <= 0)
		return true;
	else
		return false;
}

const int N = 1005;
const ll INF = 0x3f3f3f3f;

bool cmp(Point a, Point b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

int n;
struct Rec {
	Point a[2], b[2];
	Rec() {}
	Rec(ll l, ll r, ll u, ll d) {
		a[0] = Point(l, u); b[0] = Point(r, d);
		a[1] = Point(r, u); b[1] = Point(l, d);
	}
	void init() {
		Point tmp[4];
		for (int i = 0; i < 4; i++)
			tmp[i].read();
		sort(tmp, tmp + 4, cmp);
		b[1] = tmp[0];
		a[0] = tmp[1];
		b[0] = tmp[2];
		a[1] = tmp[3];
		/*
		if (tmp[0].x != tmp[1].x) while(1);
		if (tmp[2].x != tmp[3].x) while(1);
		if (tmp[0].y != tmp[2].y) while(1);
		if (tmp[1].y != tmp[3].y) while(1);
		*/
	}
} rec[N];

int main() {
	while (~scanf("%d", &n) && n) {
		gao.init(n);
		//ll x, y;
		//ll l, r, u, d;
		for (int i = 0; i < n; i++) {
			//l = d = INF; r = u = -INF;
			/*for (int j = 0; j < 4; j++) {
				scanf("%lld%lld", &x, &y);
				l = min(l, x); r = max(r, x);
				d = min(d, y); u = max(u, y);
			}
			rec[i] = Rec(l, r, u, d);*/
			rec[i].init();
			for (int j = 0; j < i; j++) {
				for (int x = 0; x < 2; x++)
					for (int y = 0; y < 2; y++) {
						if (judge(rec[i].a[x], rec[i].b[x], rec[j].a[y], rec[j].b[y]))
							gao.add_Edge(i, x, j, y);
					}
			}
		}
		printf("%s\n", gao.solve() ? "YES" : "NO");
	}
	return 0;
}

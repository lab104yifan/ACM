#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdlib>
#include <set>
#include <algorithm>
using namespace std;

const int N = 1005;

typedef long long ll;
typedef pair<int, int> pii;
#define MP(a,b) make_pair(a,b)

vector<int> g[N];
int t, n, vis[N];
ll l;

struct Point {
    ll x, y;
    int id;
} p[N];

bool cmp(Point a, Point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

ll gcd(ll a, ll b) {
    if (!b) return a;
    return gcd(b, a % b);
}

bool dis(Point a, Point b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx * dx + dy * dy <= l * l;
}

void build() {
    sort(p, p + n + 1, cmp);
    for (int i = 0; i <= n + 1; i++) {
	set<pii> save;
	for (int j = i + 1; j <= n + 1; j++) {
	    if (dis(p[i], p[j])) {
		ll dx = p[i].x - p[j].x;
		ll dy = p[i].y - p[j].y;
		ll d = gcd(dx, dy);
		dx /= d; dy /= d;
		if (save.find(MP(dx, dy)) != save.end()) continue;
		save.insert(MP(dx, dy));
		g[p[i].id].push_back(p[j].id);
		g[p[j].id].push_back(p[i].id);
	    }
	}
    }
}

bool solve() {
    queue<int> Q;
    memset(vis, -1, sizeof(vis));
    Q.push(0);
    vis[0] = 0;
    while (!Q.empty()) {
	int now = Q.front();
	if (now == n + 1) {
	    printf("%d\n", vis[now] - 1);
	    return true;
	}
	Q.pop();
	for (int i = 0; i < g[now].size(); i++) {
	    int v = g[now][i];
	    if (vis[v] != -1) continue;
	    vis[v] = vis[now] + 1;
	    Q.push(v);
	}
    }
    return false;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%lld", &n, &l);
	scanf("%lld%lld", &p[0].x, &p[0].y);
	p[0].id = 0; p[n + 1].id = n + 1;
	scanf("%lld%lld", &p[n + 1].x, &p[n + 1].y);
	g[0].clear(); g[n + 1].clear();
	for (int i = 1; i <= n; i++) {
	    g[i].clear();
	    scanf("%lld%lld", &p[i].x, &p[i].y);
	    p[i].id = i;
	}
	build();
	if (!solve()) printf("impossible\n");
    }
    return 0;
}

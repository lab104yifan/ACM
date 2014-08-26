#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;

const int N = 505;
const int D[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int t, h, w, d, g[N][N], vis[N][N];

struct Point {
    int x, y, val;
    Point(int x, int y, int val = 0) {
	this->x = x;
	this->y = y;
	this->val = val;
    }
    bool operator < (const Point& a) const {
	return val < a.val;
    }
};

priority_queue<Point> Q;

int bfs(int x, int y, int H) {
    queue<Point> Q;
    Q.push(Point(x, y));
    vis[x][y] = H;
    int ans = 1;
    int flag = 1;
    while (!Q.empty()) {
	Point u = Q.front();
	Q.pop();
	for (int i = 0; i < 4; i++) {
	    int xx = u.x + D[i][0];
	    int yy = u.y + D[i][1];
	    if (xx < 0 || xx >= h || yy < 0 || yy >= w) continue;
	    if (H - g[xx][yy] >= d) continue;
	    if (vis[xx][yy] > H) {
		flag = 0;
		continue;
	    }
	    if (vis[xx][yy] == H) continue;
	    if (g[xx][yy] == H) ans++;
	    vis[xx][yy] = H;
	    Q.push(Point(xx, yy));
	}
    }
    if (flag) return ans;
    return 0;
}

int solve() {
    memset(vis, -1, sizeof(vis));
    int ans = 0;
    while (!Q.empty()) {
	Point u = Q.top();
	Q.pop();
	if (vis[u.x][u.y] != -1) continue;
	ans += bfs(u.x, u.y, g[u.x][u.y]);
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d%d", &h, &w, &d);
	for (int i = 0; i < h; i++) {
	    for (int j = 0; j < w; j++) {
		scanf("%d", &g[i][j]);
		Q.push(Point(i, j, g[i][j]));
	    }
	}
	printf("%d\n", solve());
    }
    return 0;
}

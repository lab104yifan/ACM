#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int N = 105;
int n, m, k, g[10][10], vis[10];
char str[N][N];

struct Point {
    int x, y, num;
    Point(int x = 0, int y = 0) {
	this->x = x;
	this->y = y;
    }
} s, p[10];

int bfs(Point a, Point b) {
    queue<Point> Q;
    a.num = 0;
    Q.push(a);
    int vis[N][N];
    memset(vis, 0, sizeof(vis));
    vis[a.x][a.y] = 1;
    while (!Q.empty()) {
	Point now = Q.front();
	if (now.x == b.x && now.y == b.y) return now.num;
	Q.pop();
	for (int i = 0; i < 4; i++) {
	    int xx = now.x + d[i][0];
	    int yy = now.y + d[i][1];
	    if (xx <= 0 || xx > n || yy <= 0 || yy > m || str[xx][yy] == '#'|| vis[xx][yy]) continue;
	    Point next = Point(xx, yy);
	    next.num = now.num + 1;
	    vis[next.x][next.y] = 1;
	    Q.push(next);
	}
    }
    return -1;
}

bool build() {
    memset(g, -1, sizeof(g));
    for (int i = 0; i < k; i++) {
	g[0][i + 1] = bfs(s, p[i]);
	for (int j = i + 1; j < k; j++)
	    g[i + 1][j + 1] = g[j + 1][i + 1] = bfs(p[i], p[j]);
    }
    return true;
}

int dfs(int now, int num) {
    if (num == k) return 0;
    int ans = INF;
    for (int i = 1; i <= k; i++) {
	if (g[now][i] == -1 || vis[i]) continue;
	vis[i] = 1;
	ans = min(ans, dfs(i, num + 1) + g[now][i]);
	vis[i] = 0;
    }
    return ans;
}

int main() {
    while (~scanf("%d%d", &n, &m) && n || m) {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
	    scanf("%s", str[i] + 1);
	    for (int j = 1; j <= m; j++) {
		if (str[i][j] == '@')
		    s = Point(i, j);
	    }
	}
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
	    scanf("%d%d", &p[i].x, &p[i].y);
	if (!build()) printf("-1\n");
	else printf("%d\n", dfs(0, 0));
    }
    return 0;
}

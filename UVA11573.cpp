#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int d[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
const int N = 1005;

int n, m, vis[N][N];
char g[N][N];

struct Node {
	int x, y, val;
	Node() {}
	Node(int x, int y, int val) {
		this->x = x;
		this->y = y;
		this->val = val;
	}
	bool operator < (const Node& c) const {
		return val > c.val;
	}
	void read() {
		scanf("%d%d", &x, &y);
	}
}s, e;

int bfs() {
	priority_queue<Node> Q;
	s.val = 0;
	Q.push(s);
	memset(vis, -1, sizeof(vis));
	vis[s.x][s.y] = 0;
	while (!Q.empty()) {
		Node u = Q.top();
		if (u.x == e.x && u.y == e.y) return u.val;
		Q.pop();
		for (int i = 0; i < 8; i++) {
			int xx = u.x + d[i][0];
			int yy = u.y + d[i][1];
			int val = u.val;
			if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
			if (i != g[u.x][u.y] - '0')
				val++;
			if (vis[xx][yy] == -1 || val < vis[xx][yy]) {
				vis[xx][yy] = val;
				Q.push(Node(xx, yy, val));
			}
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++)
			scanf("%s", g[i] + 1);
		int q;
		scanf("%d", &q);
		while (q--) {
			s.read();
			e.read();
			printf("%d\n", bfs());
		}
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 205;

struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
} p[N];

double dis(Point a, Point b) {
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

struct Edge {
	int u, v;
	double d;
	Edge() {}
	Edge(int u, int v) {
		this->u = u;
		this->v = v;
		d = dis(p[u], p[v]);
	}
	bool operator < (const Edge& c) const {
		return d < c.d;
	}
} E[N * N];

int n, en, parent[N];

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

int main() {
	int cas = 0;
	while (~scanf("%d", &n) && n) {
		en = 0;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			p[i].read();
			for (int j = 0; j < i; j++)
				E[en++] = Edge(i, j);
		}
		sort(E, E + en);
		for (int i = 0; i < en; i++) {
			int pa = find(E[i].u);
			int pb = find(E[i].v);
			if (pa != pb)
				parent[pa] = pb;
			if (find(0) == find(1)) {
				printf("Scenario #%d\nFrog Distance = %.3lf\n\n", ++cas, E[i].d);
				break;
			}
		}
	}
	return 0;
}

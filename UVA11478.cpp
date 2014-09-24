#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef int Type;

const int MAXNODE = 505;
const int MAXEDGE = 2777;

struct Edge {
	int u, v;
	Type dist;
	Edge() {}
	Edge(int u, int v, Type dist) {
		this->u = u;
		this->v = v;
		this->dist = dist;
	}
};

struct BellmanFrod {
	int n, m;
	Edge edges[MAXEDGE];
	int first[MAXNODE];
	int next[MAXEDGE];
	bool inq[MAXNODE];
	Type d[MAXNODE];
	int p[MAXNODE];
	int cnt[MAXNODE];

	void init(int n) {
		this->n = n;
		memset(first, -1, sizeof(first));
		m = 0;
	}

	void add_Edge(int u, int v, Type dist) {
		edges[m] = Edge(u, v, dist);
		next[m] = first[u];
		first[u] = m++;
	}

	bool negativeCycle() {
		queue<int> Q;
		memset(inq, 0, sizeof(inq));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++) {
			d[i] = 0; inq[i] = true; Q.push(i);
		}

		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			inq[u] = false;
			for (int i = first[u]; i != -1; i = next[i]) {
				Edge& e = edges[i];
				if (d[e.v] > d[u] + e.dist) {
					d[e.v] = d[u] + e.dist;
					p[e.v] = i;
					if (!inq[e.v]) {
						Q.push(e.v);
						inq[e.v] = true;
						if (++cnt[e.v] > n) return true;
					}
				}
			}
		}
		return false;
	}
} gao;

int n, m;

bool judge(int x) {
	for (int i = 0; i < gao.m; i++)
		gao.edges[i].dist -= x;
	bool tmp = gao.negativeCycle();
	for (int i = 0; i < gao.m; i++)
		gao.edges[i].dist += x;
	return tmp;
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		gao.init(n);
		int u, v, dist;
		int l = 1, r = 0;
		while (m--) {
			scanf("%d%d%d", &u, &v, &dist);
			u--, v--; r = max(r, dist);
			gao.add_Edge(u, v, dist);
		}
		r++;
		if (judge(l)) printf("No Solution\n");
		else if (!judge(r)) printf("Infinite\n");
		else {
			while (l < r) {
				int mid = (l + r) / 2;
				if (judge(mid)) r = mid;
				else l = mid + 1;
			}
			printf("%d\n", l - 1);
		}
	}
	return 0;
}

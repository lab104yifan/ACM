#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int N = 1005;
const int M = 25005;

int n, m;

struct Edge {
	int u, v, val, id;
	void read(int id) {
		scanf("%d%d%d", &u, &v, &val);
		this->id = id;
	}
} e[M];

bool cmp(Edge a, Edge b) {
	return a.val < b.val;
}

int parent[N];

int find(int x) {
	return x == parent[x] ? x : parent[x] = find(parent[x]);
}

int main() {
	while (~scanf("%d%d", &n, &m) && n || m) {
		for (int i = 0; i < n; i++) parent[i] = i;
		for (int i = 0; i < m; i++) e[i].read(i);
		sort(e, e + m, cmp);
		int bo = 0;
		for (int i = 0; i < m; i++) {
			int pu = find(e[i].u);
			int pv = find(e[i].v);
			if (pu != pv)
				parent[pu] = pv;
			else {
				if (bo) printf(" ");
				else bo = 1;
				printf("%d", e[i].val);
			}
		}
		if (!bo) printf("forest");
		printf("\n");
	}
	return 0;
}

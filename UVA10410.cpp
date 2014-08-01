#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int N = 1005;

int n, b[N], d[N], now;
vector<int> g[N];

struct Seg {
    int l, r;
    Seg(){}
    Seg(int l, int r) {
	this->l = l;
	this->r = r;
    }
};

void bfs() {
    now = 1;
    queue<Seg> Q;
    Q.push(Seg(0, n));
    while (!Q.empty()) {
	Seg p = Q.front();
	Q.pop();
	int u = d[p.l];
	if (now == n || p.l + 1 == p.r) continue;
	int pre = p.l + 1;
	g[u].push_back(d[pre]);
	now++;
	for (int i = p.l + 2; i < p.r; i++) {
	    if (b[now] == d[i]) {
		g[u].push_back(d[i]);
		Q.push(Seg(pre, i));
		pre = i;
		now++;
	    }
	}
	if (pre < p.r)
	    Q.push(Seg(pre, p.r));
    }
}

int main() {
    while (~scanf("%d", &n)) {
	for (int i = 0; i < n; i++) {
	    g[i + 1].clear();
	    scanf("%d", &b[i]);
	}
	for (int i = 0; i < n; i++)
	    scanf("%d", &d[i]);
	bfs();
	for (int i = 1; i <= n; i++) {
	    printf("%d:", i);
	    for (int j = 0; j < g[i].size(); j++)
		printf(" %d", g[i][j]);
	    printf("\n");
	}
    }
    return 0;
}

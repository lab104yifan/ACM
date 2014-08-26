#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXNODE = 1111111;

const int N = 21;
const int MOD = 9999991;

int C[N][N];

struct BST {
    struct Node {
	int l, r, val, lsz, rsz;
	Node() {l = 0, r = 0, val = -1; lsz = 0; rsz = 0;}
    } node[MAXNODE];

    int sz;

    void init() {
	node[1] = Node();
	sz = 2;
    }

    void insert(int x, int v) {
	if (node[x].val == -1) {
	    node[x].val = v;
	    return;
	}
	if (v < node[x].val) {
	    if (!node[x].l) {
		node[sz] = Node();
		node[x].l = sz++;
	    }
	    insert(node[x].l, v);
	    node[x].lsz++;
	}
	else {
	    if (!node[x].r) {
		node[sz] = Node();
		node[x].r = sz++;
	    }
	    insert(node[x].r, v);
	    node[x].rsz++;
	}
    }

    int dfs(int x) {
	if (x == 0) return 1;
	return (ll)dfs(node[x].l) * dfs(node[x].r) % MOD * C[node[x].lsz + node[x].rsz][node[x].lsz] % MOD;
    }

    void solve() {
	init();
	int n, num;
	scanf("%d", &n);
	while (n--) {
	    scanf("%d", &num);
	    insert(1, num);
	}
	printf("%d\n", dfs(1));
    }

} gao;

int t;

void getC() {
    for (int i = 0; i < N; i++) {
	C[i][0] = C[i][i] = 1;
	for (int j = 1; j < i; j++)
	    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

int main() {
    getC();
    scanf("%d", &t);
    while (t--) {
	gao.solve();
    }
    return 0;
}

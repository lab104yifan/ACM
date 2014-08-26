#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 20005;

int n, qn, parent[N], val[N], vis[N];
struct query {
    char c;
    int a, b, v, k, x[20];
} q[2 * N];

int find(int x) {
    if (x == parent[x]) return x;
    int tmp = parent[x];
    parent[x] = find(parent[x]);
    val[x] ^= val[tmp];
    return parent[x];
}

void init() {
    for (int i = 0; i <= n; i++) {
	parent[i] = i;
	val[i] = 0;
    }
    char Q[105];
    for (int i = 0; i < qn; i++) {
	scanf("%s", Q);
	q[i].c = Q[0];
	int a, b, v;
	if (Q[0] == 'I') {
	    gets(Q);
	    if (sscanf(Q, "%d%d%d", &a, &b, &v) == 2) {
		v = b; b = n;
	    }
	    q[i].a = a; q[i].b = b; q[i].v = v;
	}
	else {
	    scanf("%d", &q[i].k);
	    for (int j = 0; j < q[i].k; j++)
		scanf("%d", &q[i].x[j]);
	}
    }
}

void solve() {
    int fir = 0;
    for (int i = 0; i < qn; i++) {
	if (q[i].c == 'I') {
	    fir++;
	    int pa = find(q[i].a);
	    int pb = find(q[i].b);
	    if (pa == n) swap(pa, pb);
	    if (pa == pb) {
		if ((val[q[i].a]^val[q[i].b]) != q[i].v) {
		    printf("The first %d facts are conflicting.\n", fir);
		    return;
		}
	    }
	    else {
		parent[pa] = pb;
		val[pa] = val[q[i].a]^val[q[i].b]^q[i].v;
	    }
	}
	else {
	    int ans = 0;
	    for (int j = 0; j < q[i].k; j++) {
		int px = find(q[i].x[j]);
		ans ^= val[q[i].x[j]];
		if (px != n)
		    vis[px] ^= 1;
	    }
	    int flag = 1;
	    for (int j = 0; j < q[i].k; j++) {
		if (vis[parent[q[i].x[j]]])
		    flag = 0;
		vis[parent[q[i].x[j]]] = 0;
	    }
	    if (flag) printf("%d\n", ans);
	    else printf("I don't know.\n");
	}
    }
}

int main() {
    int cas = 0;
    while (~scanf("%d%d", &n, &qn) && n) {
	init();
	printf("Case %d:\n", ++cas);
	solve();
	printf("\n");
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
#define lson(x) ((x<<1) + 1)
#define rson(x) ((x<<1) + 2)

const int N = 100005;

int n, m, shif[35], sn, num[N];
char Q[1005];

struct Node {
    int l, r, Min;
} node[4 * N];

void handle(char *Q) {
    int len = strlen(Q);
    int num = -1;
    sn = 0;
    for (int i = 0; i < len; i++) {
	if (Q[i] >= '0' && Q[i] <= '9') {
	    if (num == -1) num = Q[i] - '0';
	    else num = num * 10 + Q[i] - '0';
	}
	else {
	    if (num != -1) {
		shif[sn++] = num;
		num = -1;
	    }
	}
    }
    sort(shif, shif + sn);
}

void build(int l, int r, int x = 0) {
    node[x].l = l; node[x].r = r;
    if (l == r) {
	node[x].Min = num[l];
	return;
    }
    int mid = (l + r) / 2;
    build(l, mid, lson(x));
    build(mid + 1, r, rson(x));
    node[x].Min = min(node[lson(x)].Min, node[rson(x)].Min);
}

void set(int k, int v, int x = 0) {
    if (node[x].l == node[x].r) {
	node[x].Min = v;
	return;
    }
    int mid = (node[x].l + node[x].r) / 2;
    if (k <= mid) set(k, v, lson(x));
    if (k > mid) set(k, v, rson(x));
    node[x].Min = min(node[lson(x)].Min, node[rson(x)].Min);
}

int query(int l, int r, int x = 0) {
    if (node[x].l >= l && node[x].r <= r)
	return node[x].Min;
    int mid = (node[x].l + node[x].r) / 2;
    int ans = INF;
    if (l <= mid) ans = min(ans, query(l, r, lson(x)));
    if (r > mid) ans = min(ans, query(l, r, rson(x)));
    return ans;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
	for (int i = 1; i <= n; i++)
	    scanf("%d", &num[i]);
	build(1, n);
	while (m--) {
	    scanf("%s", Q);
	    handle(Q);
	    if (Q[0] == 'q')
		printf("%d\n", query(shif[0], shif[1]));
	    else {
		int tmp = num[shif[0]];
		set(shif[sn - 1], num[shif[0]]);
		for (int i = 1; i < sn; i++) {
		    set(shif[i - 1], num[shif[i]]);
		    num[shif[i - 1]] = num[shif[i]];
		}
		num[shif[sn - 1]] = tmp;
	    }
	}
    }	
    return 0;
}

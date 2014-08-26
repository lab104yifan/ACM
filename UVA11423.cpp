#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define lowbit(x) (x&(-x))

const int N = 35;
const int MAXN = (1<<24) + 5;
int n, cach[N], bit[MAXN];

void add(int x, int v) {
    while (x < MAXN) {
	bit[x] += v;
	x += lowbit(x);
    }
}

int get(int x) {
    int ans = 0;
    while (x) {
	ans += bit[x];
	x -= lowbit(x);
    }
    return ans;
}

int get(int l, int r) {
    return get(r) - get(l - 1);
}

char op[10];
int ans[N], vis[MAXN], now;

void init() {
    now = 0;
    memset(bit, 0, sizeof(bit));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++)
	scanf("%d", &cach[i]);
}

void tra(int num) {
    if (vis[num]) {
	int len = get(vis[num], now);
	for (int i = 0; i < n; i++) {
	    if (cach[i] >= len) break;
	    ans[i]++;
	}
	add(vis[num], -1);
    }
    else {
	for (int i = 0; i < n; i++)
	    ans[i]++;
    }
    add(vis[num] = ++now, 1);
}

void solve() {
    int x, b, y, nn;
    while (scanf("%s", op)) {
	if (op[0] == 'E') break;
	if (op[0] == 'S') {
	    for (int i = 0; i < n; i++)
		printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
	    memset(ans, 0, sizeof(ans));
	}
	if (op[0] == 'A') {
	    scanf("%d", &x);
	    tra(x);
	}
	if (op[0] == 'R') {
	    scanf("%d%d%d", &b, &y, &nn);
	    for (int i = 0; i < nn; i++)
		tra(b + y * i);
	}
    }
}

int main() {
    while (~scanf("%d", &n)) {
	init();
	solve();
    }
    return 0;
}

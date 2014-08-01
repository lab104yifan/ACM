#include <cstdio>
#include <cstring>

#define lowbit(x) (x&(-x))
const int N = 200005;
int t, n, m, arr[N], bit[N];

void add(int x, int v) {
    while (x < N) {
	bit[x] += v;
	x += lowbit(x);
    }
}

int query(int x) {
    int ans = 0;
    while (x) {
	ans += bit[x];
	x -= lowbit(x);
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	memset(bit, 0, sizeof(bit));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
	    arr[i] = n + 1 - i;
	    add(i, 1);
	}
	int v;
	for (int i = 1; i <= m; i++) {
	    scanf("%d", &v);
	    int under = query(arr[v]);
	    printf("%d%c", n - under, i == m ? '\n' : ' ');
	    add(arr[v], -1);
	    arr[v] = n + i;
	    add(n + i, 1);
	}
    }
    return 0;
}

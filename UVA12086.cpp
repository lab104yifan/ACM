#include <cstdio>
#include <cstring>

#define lowbit(x) (x&(-x))

const int N = 200005;

int n, bit[N], num[N];

void add(int x, int v) {
    while (x <= n) {
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

int query(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	if (cas) printf("\n");
	int a, b;
	memset(bit, 0, sizeof(bit));
	for (int i = 1; i <= n; i++) {
	    scanf("%d", &num[i]);
	    add(i, num[i]);
	}
	char Q[10];
	printf("Case %d:\n", ++cas);
	while (~scanf("%s", Q) && Q[0] != 'E') {
	    scanf("%d%d", &a, &b);
	    if (Q[0] == 'M')
		printf("%d\n", query(a, b));
	    else {
		add(a, b - num[a]);
		num[a] = b;
	    }
	}
    }
    return 0;
}

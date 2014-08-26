#include <cstdio>
#include <cstring>

#define lowbit(x) (x&(-x))
const int N = 66666;

typedef long long ll;

int n, bit[16][N], mi[20];

void add(int i, int x, int v) {
    while (x < N) {
	bit[i][x] += v;
	x += lowbit(x);
    }
}

int get(int i, int x) {
    int ans = 0;
    while (x) {
	ans += bit[i][x];
	x -= lowbit(x);
    }
    return ans;
}

void init() {
    memset(bit, 0, sizeof(bit));
    int num;
    while (n--) {
	scanf("%d", &num);
	for (int i = 1; i <= 16; i++) {
	    add(i - 1, num % mi[i] + 1, 1);
	}
    }
}

ll solve() {
    char op[2];
    int d, sum = 0;
    ll ans = 0;
    while (scanf("%s", op)) {
	if (op[0] == 'E') break;
	scanf("%d", &d);
	if (op[0] == 'C')
	    sum = (sum + d) % mi[16];
	else {
	    int tmp = sum % mi[d];
	    if (sum&mi[d])
		ans += get(d, mi[d] - tmp) + get(d, mi[d + 1]) - get(d, mi[d + 1] - tmp);
	    else ans += get(d, mi[d + 1] - tmp) - get(d, mi[d] - tmp);
	}
    }
    return ans;
}

int main() {
    int cas = 0;
    mi[0] = 1;
    for (int i = 1; i <= 16; i++)
	mi[i] = mi[i - 1] * 2;
    while (~scanf("%d", &n) && n != -1) {
	init();
	printf("Case %d: %lld\n", ++cas, solve());
    }
    return 0;
}

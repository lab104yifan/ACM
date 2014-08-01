#include <cstdio>
#include <cstring>

#define lowbit(x) (x&(-x))

const int N = 50005;

int t, k, bit[N];

void add(int x, int v) {
    while (x <= k) {
	bit[x] += v;
	x += lowbit(x);
    }
}

int get(int x) {
    int ans = 0, num = 0;
    for (int i = 16; i >= 0; i--) {
	ans += (1<<i);
	if (ans >= k || bit[ans] + num >= x)
	    ans -= (1<<i);
	else num += bit[ans];
    }
    return ans + 1;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	memset(bit, 0, sizeof(bit));
	scanf("%d", &k);
	for (int i = 1; i <= k; i++)
	    add(i, 1);
	int num;
	for (int i = 1; i <= k; i++) {
	    scanf("%d", &num);
	    num++;
	    int v = get(num);
	    printf("%d%c", v, i == k ? '\n' : ' ');
	    add(v, -1);
	}
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 35005;
int prime[N], pn = 0, vis[N];
int t, a, b;

int cal(int num) {
    int ans = 1;
    for (int i = 0; i < pn && prime[i] <= num; i++) {
	if (num % prime[i]) continue;
	int count = 1;
	while (num % prime[i] == 0) {
	    count++;
	    num /= prime[i];
	}
	ans *= count;
    }
    return ans;
}

void solve() {
    int ans, Max = 0;
    for (int i = a; i <= b; i++) {
	if (Max < cal(i)) {
	    ans = i;
	    Max = cal(i);
	}
    }
    printf("Between %d and %d, %d has a maximum of %d divisors.\n", a, b, ans, Max);
}

int main() {
    for (int i = 2; i < N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (int j = i; j < N; j += i)
	    vis[j] = 1;
    }
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &a, &b);
	solve();
    }
    return 0;
}

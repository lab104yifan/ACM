#include <stdio.h>
#include <string.h>
#include <math.h>

typedef long long LL;
const LL N = 1e6;
LL prime[N * 10];
int pn = 0;
bool vis[N];

bool judge(long long num) {
    long long m = sqrt(num);
    for (int i = 0; i < pn && prime[i] <= m; i++)
	if (num % prime[i] == 0) return false;
    return true;
}

void init() {
    for (LL i = 2; i <= N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (LL j = i * i; j <= N; j += i)
	    vis[j] = true;
    }
    for (LL i = 1; i < 20; i++) {
	long long Max = (i + 1) * N;
	memset(vis, false, sizeof(vis));
	for (LL j = N * i + 1; j <= Max; j++) {
	    if (vis[j - i * N]) continue;
	    if (judge(j))
		prime[pn++] = j;
	    for (LL k = j * j; k <= Max; k += j)
		vis[k - i * N] = true;
	} 
    }
    printf("%d\n", pn);
}

int main() {
    init();
    return 0;
}

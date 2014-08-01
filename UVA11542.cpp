#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long N = 501;

int t, n, a[N][N], Max, vis[N], pn = 0;
long long prime[N];

void get_prime() {
    for (long long i = 2; i < N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (long long j = i * i; j < N; j += i)
	    vis[j] = 1;
    }
}

int gauss() {
    int i = 0, j = 0;
    while (i <= Max && j < n) {
	int k = i;
	for (; k <= Max; k++)
	    if (a[k][j]) break;
	if (k != Max + 1) {
	    for (int l = 0; l <= n; l++)
		swap(a[i][l], a[k][l]);
	    for (int k = i + 1; k <= Max; k++) {
		if (a[k][j]) {
		    for (int l = j; l <= n; l++)
			a[k][l] ^= a[i][l];
		}
	    }
	    i++;
	}
	j++;
    }
    return n - i;
}

int main() {
    get_prime();
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	long long x;
	Max = 0;
	memset(a, 0, sizeof(a));
	for (int i = 0; i < n; i++) {
	    scanf("%lld", &x);
	    for (int j = 0; j < pn && prime[j] <= x; j++) {
		while (x % prime[j] == 0) {
		    a[j][i] ^= 1;
		    Max = max(Max, j);
		    x /= prime[j];
		}
	    }
	}
	printf("%lld\n", (1LL<<(gauss())) - 1);
    }
    return 0;
}

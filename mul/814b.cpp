#include <cstdio>
#include <cstring>

typedef long long ll;
ll n, k;

int main() {
    int cas = 0;
    while (scanf("%I64d%I64d", &n, &k) && n || k) {
	for (ll i = 1; i < k; i++) {
	    if (n < (i + 1))
		break;
	    n = n - n / (i + 1);
	}
	printf("Case #%d: %I64d\n", ++cas, (ll)n * k);
    }
    return 0;
}

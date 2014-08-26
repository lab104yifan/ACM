#include <cstdio>
#include <cstring>

typedef unsigned long long ll;

const ll MOD = (1ULL<<32);
const int N = 500001;

int t, n;
ll ans[N], frc[N];

void init() {
    for (ll i = 1; i < N; i++) {
	for (ll j = i; j < N; j += i) {
	    ll tmp = j / i;
	    frc[j] = (frc[j] + j * (tmp + 1) * tmp / 2 % MOD) % MOD;
	}
    }
    for (int i = 1; i < N; i++)
	ans[i] = (ans[i - 1] + frc[i]) % MOD;
}

int main() {
    init();
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	printf("Case #%d: %I64u\n", ++cas, ans[n]);
    }
    return 0;
}

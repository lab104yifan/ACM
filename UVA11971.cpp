#include <cstdio>
#include <cstring>

const int N = 55;
typedef long long ll;

int t, k;
ll mi[N];

ll gcd(ll a, ll b) {
    while (b) {
	ll tmp = b;
	b = a % b;
	a = tmp;
    }
    return a;
}

int main() {
    mi[0] = 1;
    for (int i = 1; i <= 50; i++)
	mi[i] = mi[i - 1] * 2;
    scanf("%d", &t);
    int cas = 0;
    while (t--) {
	scanf("%*d%d", &k);
	printf("Case #%d: ", ++cas);
	if (k == 1) {
	    printf("0/1\n");
	    continue;
	}
	ll zi = mi[k] - k - 1;
	ll mu = mi[k];
	ll d = gcd(zi, mu);
	printf("%lld/%lld\n", zi / d, mu / d);
    }
    return 0;
}

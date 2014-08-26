#include <cstdio>
#include <cstring>

typedef long long ll;
ll h, a, b, k;

bool solve() {
    if (a >= h) return true;
    if (b >= a) return false;
    if (h - (k - 1) * a + b * (k - 1) <= a) return true;
    ll s = -a * k + b * (k + 1);
    if (s >= 0) return false;
    return true;
}

int main() {
    int cas = 0;
    while (~scanf("%I64d%I64d%I64d%I64d", &h, &a, &b, &k) && h) {
	printf("Case #%d: ", ++cas);
	printf("%s\n", solve() ? "YES" : "NO");
    }
    return 0;
}

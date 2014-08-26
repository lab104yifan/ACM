#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

int t;
ll l, r;

bool judge(ll num) {
    ll flag = 1;
    ll ans = 0;
    while (num) {
	ans += num % 10 * flag;
	flag *= -1;
	num /= 10;
    }
    return (ans == 3);
}

ll solve() {
    ll i = l;
    for (; i <= r; i++)
	if (i % 11 == 3)
	    break;
    for (; i <= r; i += 11) {
	if (!judge(i)) return i;
    }
    return -1;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%I64d%I64d", &l, &r);
	printf("%I64d\n", solve());
    }
    return 0;
}

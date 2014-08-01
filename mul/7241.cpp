#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;

int n;
struct Q {
    __int64 e, k;
} q[N];

bool cmp(Q a, Q b) {
    return a.e * b.k < a.k * b.e;
}

int main() {
    while (~scanf("%d", &n)) {
	for (int i = 0; i < n; i++)
	    scanf("%I64d", &q[i].e);
	for (int i = 0; i < n; i++)
	    scanf("%I64d", &q[i].k);
	sort(q, q + n, cmp);
	long long ans = 0, now = 0;
	for (int i = 0; i < n; i++) {
	    now += q[i].e;
	    ans += now * q[i].k;
	}
	printf("%I64d\n", ans);
    }
    return 0;
}

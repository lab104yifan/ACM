#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 45;

struct SB {
    int a, b;
} sb[N];

bool cmp(SB x, SB y) {
    return x.a > y.a;
}

int t, n, v;

double solve() {
    for (int i = 0; i < n; i++)
	if (sb[i].b && sb[i].a >= v) return -1;
    double ans = 0;
    for (int i = 0; i < n; i++)
	ans = ans + (sb[i].b + sb[i].a * ans) / (v - sb[i].a);
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &v);
	for (int i = 0; i < n; i++)
	    scanf("%d", &sb[i].a);
	for (int i = 0; i < n; i++)
	    scanf("%d", &sb[i].b);
	sort(sb, sb + n, cmp);
	printf("%.0f\n", solve());
    }
    return 0;
}

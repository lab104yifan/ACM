#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;

int n, k;
double p[N];

void init(int n, int k) {
    memset(p, 0, sizeof(p));
    p[n - 1] = 1.0;
    for (int i = n - 1; i > 2 * k; i--) {
	p[i - 1] = p[i] * (i - 2 * k) * 1.0 / (i * 1.0) ;
    }
}

double solve(int n, int k) {
    init(n, k);
    double ans = 0;
    for (int i = 1; i <= n; i++) {
	int x = max(i - k - 1, 0) + max(n - i - k, 0);
	ans += p[x];
    }
    return n - ans;
}

int main() {
    int cas = 0;
    while (~scanf("%d%d", &n, &k) && n || k) {
	printf("Case %d: %.4lf\n", ++cas, solve(n, k));
    }
    return 0;
}

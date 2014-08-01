#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 20005;
struct Man {
    int v, t;
    Man() {}
    Man(int v, int t) {this->v = v; this->t = t;}
} m[N];

bool cmp(Man a, Man b) {
    if (a.t != b.t)
	return a.t < b.t;
    return a.v < b.v;
}

int n, t, mn;

int main() {
    scanf("%d", &t);
    while (t--) {
	mn = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
	    int a, b, c, d, e;
	    scanf("%d%d:%d%d:%d", &a, &b, &c, &d, &e);
	    int t1 = b * 60 + c;
	    int t2 = d * 60 + e;
	    m[mn++] = Man(a, t1);
	    m[mn++] = Man(-a, t2);
	}
	sort(m, m + mn, cmp);
	int ans = 0, sum = 0;
	for (int i = 0; i < mn; i++) {
	    sum += m[i].v;
	    ans = max(ans, sum);
	}
	printf("%d\n", ans);
    }
    return 0;
}

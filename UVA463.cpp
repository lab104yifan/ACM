#include <cstdio>
#include <cstring>
#include <cmath>

struct Polyno {
    double a[5];
    int len;
    
    double f(double x) {
	double ans = 0;
	for (int i = 0; i < len; i++)
	    ans += a[i] * pow(x, i);
	return ans;
    }
} p, pf;

Polyno qd(Polyno p) {
    Polyno ans;
    ans.len = p.len - 1;
    for (int i = 0; i < p.len; i++)
	ans.a[i] = p.a[i + 1] * (i + 1);
    return ans;
}

Polyno chu(Polyno p, double x) {

}

void solve() {
    for (int k = 0; k < 4; k++) {
	pf = qd(p);
	double x = 1e10;
	for (int i = 0; i < 100; i++) {
	    pre = x;
	    x = x - p.f(x) / pf.f(x);
	}
	if (fabs(x - pre) < 1e-10) {
	    p = chu(p, x);
	}
    }
}

int main() {
    while (~scanf("%lf", &p.a[4])) {
	for (int i = 3; i >= 0; i--)
	    scanf("%lf", &p.a[i]);
	p.len = 4;
	solve();
    }
    return 0;
}

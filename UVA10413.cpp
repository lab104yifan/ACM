#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
int t, n;
struct People {
    int c, p, l;
    void read() {
	scanf("%d%d%d", &c, &p, &l);
    }
} p[20];

bool cmp(People a, People b) {
    return a.l > b.l;
}

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {x = 1; y = 0; return a;}
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

bool judge(People A, People B, int mod) {
    int a = A.p - B.p;
    int b = -mod;
    int c = B.c - A.c;
    int x, y;
    int d = exgcd(a, b, x, y);
    if (c % d) return false;
    int down = -INF, up = INF;
    int tmp = min(A.l, B.l);
    if (b / d < 0) {
	down = max(down, (int)ceil((tmp * d - x * c) * 1.0 / b));
	up = min(up, (int)floor(-x * c * 1.0 / b));
    }
    else {
	down = max(down, (int)ceil(-x * c * 1.0 / b));
	up = min(up, (int)floor((tmp * d - x * c) * 1.0 / b));
    }
    return down <= up;
}

bool solve(int mod) {
    for (int i = 0; i < n; i++)
	for (int j = i + 1; j < n; j++)
	    if (judge(p[i], p[j], mod))
		return false;
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	int down = 0;
	for (int i = 0; i < n; i++) {
	    p[i].read();
	    down = max(down, p[i].c);
	}
	for (int i = down; i <= 1000000; i++) {
	    if (solve(i)) {
		printf("%d\n", i);
		break;
	    }
	}
    }
    return 0;
}

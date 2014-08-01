#include <stdio.h>
#include <string.h>

const int N = 1005;
bool vis[N][N];
long long s, x, y, dx, dy;

bool white() {
    if (x % s == 0 || y % s == 0) return false;
    if (((x / s)&1)^((y / s)&1)) return true;
    return false;
}

bool in() {
    if (x > s || y > s) {
	x -= s; y -= s;
	if (x < 0) x = s;
	if (y < 0) y = s;
    }
    if (vis[x][y]) return false;
    vis[x][y] = true;
    return true;
}

int main() {
    while (~scanf("%lld%lld%lld%lld%lld", &s, &x, &y, &dx, &dy) && s) {
	memset(vis, false, sizeof(vis));
	long long ans = 0, ansx = x, ansy = y;
	while (1) {
	    x %= 2 * s;
	    y %= 2 * s;
	    if (white()) {
		printf("After %lld jumps the flea lands at (%lld, %lld).\n", ans, ansx, ansy);
		break;
	    }
	    if (!in()) {
		printf("The flea cannot escape from black squares.\n");
		break;
	    }
	    x += dx;
	    y += dy;
	    ansx += dx;
	    ansy += dy;
	    ans++;
	}
    }
    return 0;
}

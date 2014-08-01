#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define max(a,b) ((a)>(b)?(a):(b))
const double pi = acos(-1.0);
const int d[6][2] = {{0, 2}, {0, -2}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
double l, xa, ya, xb, yb, hd, wd;
int xan, yan, xbn, ybn;

double dis(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void tra(int &x, int &y, double xa, double ya) {
    if (x % 2) {
	if (y % 2 == 0) {
	    y++;
	}
    }
    else {
	if (y % 2) {
	    y++;
	}
    }
    int minx = x, miny = y;
    double mind = dis(x * wd, y * hd, xa, ya);
    for (int i = 0; i < 6; i++) {
	double xx = (d[i][0] + x) * wd;
	double yy = (d[i][1] + y) * hd;
	if (mind > dis(xx, yy, xa, ya)) {
	    minx = d[i][0] + x;
	    miny = d[i][1] + y;
	    mind = dis(xx, yy, xa, ya);
	}
    }
    x = minx; y = miny;
}

void init() {
    hd = sin(pi/3) * l;
    wd = l + l / 2;
    xan = xa / wd;
    yan = ya / hd;
    xbn = xb / wd;
    ybn = yb / hd;
    tra(xan, yan, xa, ya); tra(xbn, ybn, xb, yb);
}

double solve() {
    if (xan == xbn && yan == ybn)
	return dis(xa, ya, xb, yb);
    int xx = abs(xbn - xan), yy = abs(ybn - yan);
    double ans = dis(xa, ya, xan * wd, yan * hd) + dis(xb, yb, xbn * wd, ybn * hd) + xx * sin(pi/3) * 2 * l;
    if (yy > xx)
	ans += (yy - xx) * l * sqrt(3) / 2;
    return ans;
}

int main() {
    while (~scanf("%lf%lf%lf%lf%lf", &l, &xa, &ya, &xb, &yb) && l || xa || ya || xb || yb) {
	init();
	printf("%.3lf\n", solve());
    }
    return 0;
}

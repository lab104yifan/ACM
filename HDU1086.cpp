#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 105;

struct Point {
	double x, y;
	Point() {}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void read() {
		cin >> x >> y;
	}
} p[N][2];

double xmul(Point a, Point b, Point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool judge(Point a1, Point b1, Point a2, Point b2) {
	if (min(a1.x, b1.x) <= max(a2.x, b2.x) &&
		min(a1.y, b1.y) <= max(a2.y, b2.y) &&
		min(a2.x, b2.x) <= max(a1.x, b1.x) &&
		min(a2.y, b2.y) <= max(a1.y, b1.y) && 
		xmul(a1, a2, b1) * xmul(a1, b2, b1) <= 0 &&
		xmul(a2, a1, b2) * xmul(a2, b1, b2) <= 0)
		return true;
	else
		return false;
}

int n;

int main() {
	while (cin >> n) {
		if (n == 0) break;
		int ans = 0;
		for (int i = 0; i < n; i++) {
			p[i][0].read(); 
			p[i][1].read();
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++)
				if (judge(p[i][0], p[i][1], p[j][0], p[j][1]))
					ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}

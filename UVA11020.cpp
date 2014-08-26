#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;

int t, n;
struct Point {
    int x, y;
    bool operator < (const Point &c) const {
	if (x == c.x) return y < c.y;
	return x < c.x;
    }
};

multiset<Point> s;
multiset<Point>::iterator it;

int main() {
    int cas = 0;
    cin >> t;
    while (t--) {
	s.clear();
	cin >> n;
	Point u;
	cout << "Case #" << ++cas << ":" << endl;
	while (n--) {
	    cin >> u.x >> u.y;
	    it = s.lower_bound(u);
	    if (it == s.begin() || (--it)->y > u.y) {
		s.insert(u);
		it = s.upper_bound(u);
		while (it != s.end() && it->y >= u.y) s.erase(it++);
	    }
	    cout << s.size() << endl;
	}
	if (t) cout << endl;
    }
    return 0;
}

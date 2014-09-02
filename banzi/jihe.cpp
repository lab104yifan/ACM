struct Point {
	ll x, y;
	Point() {}
	Point(ll x, ll y) {
		this->x = x;
		this->y = y;
	}
	void read() {
		scanf("%lld%lld", &x, &y);
	}
};

int xmul(Point a, Point b, Point c) {
	ll ans = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (ans == 0) return 0;
	if (ans > 0) return 1;
	return -1;
}

bool interse(Point a1, Point b1, Point a2, Point b2) {
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

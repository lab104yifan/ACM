int lowbit(int x) {
    return (x&(-x));
}

void add(int x, int v) {
    while (x < N) {
	bit[x] += v;
	x += lowbit(x);
    }
}

//normal find
int find(int x) {
    int ans = 0;
    while (x) {
	ans += bit[x];
	x -= lowbit(x);
    }
    return ans;
}

//find Kth big
int find(int x) {
    int ans = 0, num = 0;
    for (int i = 20; i >= 0; i--) {
	ans += (1<<i);
	if (ans >= N || num + bit[ans] >= x)
	    ans -= (1<<i);
	else num += bit[ans];
    }
    return ans + 1;
}

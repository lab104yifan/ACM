#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 100005;
int n, num[N], save[N], sn;

void init() {
    for (int i = 0; i < n; i++)
	scanf("%d", &num[i]);
}

long long solve(int l, int r, int *num) {
    if (r - l < 1) return 0;
    int mid = (l + r) / 2;
    long long ans = solve(l, mid, num) + solve(mid + 1, r, num);
    sn = l;
    int ll = l, rr = mid + 1;
    while (ll <= mid && rr <= r) {
	if (num[ll] <= num[rr])
	    save[sn++] = num[ll++];
	else {
	    ans += (mid + 1 - ll);
	    save[sn++] = num[rr++];
	}
    }
    while (ll <= mid) save[sn++] = num[ll++];
    while (rr <= r) save[sn++] = num[rr++];
    for (int i = l; i <= r; i++)
	num[i] = save[i];
    return ans;
}

long long k;

int main() {
    while (~scanf("%d%I64d", &n, &k)) {
	init();
	long long ans = solve(0, n - 1, num);
	ans = max(ans - k, 0LL);
	printf("%I64d\n", ans);
    }
    return 0;
}

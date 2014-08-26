#include <cstdio>
#include <cstring>

const int N = 1000005;

typedef long long ll;

int t, n, a[N], save[N], v;

ll cal(int *a, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    int sl = l, sr = r;
    ll ans = cal(a, l, mid) + cal(a, mid + 1, r);
    int tmp = mid; mid++;
    for (int i = l; i <= r; i++) {
	if (l <= tmp && mid <= r) {
	    if (a[l] <= a[mid]) save[i] = a[l++];
	    else {
		ans += mid - i;
		save[i] = a[mid++];
	    }
	}
	else if (l <= tmp) save[i] = a[l++];
	else if (mid <= r) save[i] = a[mid++];
    }
    for (int i = sl; i <= sr; i++)
	a[i] = save[i];
    return ans;
}

bool judge() {
    ll nx = cal(a, 0, n * n * n - 2);
    if (n&1) {
	if (nx&1) return false;
    }
    else {
	int z[3];
	for (int i = 0; i < 3; i++) {
	    z[i] = v % n;
	    v /= n;
	}
	ll bu = 2 * n - 2 - z[2] - z[1];
	if ((bu^nx)&1) return false;
    }
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	int flag = 0;
	for (int k = 0; k < n; k++) {
	    for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		    int now = n * n * k + n * i + j - flag;
		    scanf("%d", &a[now]);
		    if (a[now] == 0) {
			v = now;
			flag = 1;
		    }
		}
	    }
	}
	if (judge()) printf("Puzzle can be solved.\n");
	else printf("Puzzle is unsolvable.\n");
    }
    return 0;
}

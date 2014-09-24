#include <cstdio>
#include <cstring>

typedef long long ll;

int t, d, a[15];

int bitcount(int x) {
	int ans = 0;
	while (x) {
		ans += (x&1);
		x >>= 1;
	}
	return ans;
}

int gcd(int a, int b) {
	while (b) {
		int tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &d);
		for (int i = 0; i < d; i++)
			scanf("%d", &a[i]);
		int tmp;
		for (int i = 0; i < d; i++) {
			scanf("%d", &tmp);
			a[i] -= tmp;
			if (a[i] < 0) a[i] = -a[i];
		}
		ll ans = 0;
		for (int i = 0; i < (1<<d); i++) {
			int cnt = bitcount(i);
			int sum = 0;
			for (int j = 0; j < d; j++) {
				if (i&(1<<j))
					sum = gcd(sum, a[j]);
			}
			if (cnt&1) ans += sum;
			else ans -= sum;
		}
		printf("Case %d: %lld\n", ++cas, ans);
	}
	return 0;
}

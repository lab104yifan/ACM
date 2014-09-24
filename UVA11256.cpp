#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long t, n, mi[10];

long long count(long long x) {
	long long ans = 0;
	while (x) {
		x /= 10;
		ans++;
	}
	return ans;
}

long long gcd(long long a, long long b) {
	while (b) {
		long long tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int main() {
	mi[0] = 1;
	for (long long i = 1; i < 10; i++)
		mi[i] = mi[i - 1] * 10;
	scanf("%lld", &t);
	while (t--) {
		long long ans = 999999999999999999;
		scanf("%lld", &n);
		long long len = count(n);
		for (long long i = 1; i <= len; i++) {
			long long num = 1;
			for (long long j = i + i; j <= 2 * len; j += i) {
				num = num * mi[i] + 1;
				long long yu = n / gcd(num, n);
				if (count(yu) <= i) {
					long long tmp = mi[i - 1] / yu * yu;
					if (tmp < mi[i - 1]) tmp += yu;
					ans = min(ans, num * tmp);
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

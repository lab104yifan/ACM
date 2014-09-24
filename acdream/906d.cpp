#include <cstdio>
#include <cstring>

int gcd(int a, int b) {
	while (b) {
		int tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int n;

int main() {
	while (~scanf("%d", &n)) {
		int a, b;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			int mu = b + 1;
			int d = gcd(a, mu);
			a /= d; mu /= d;
			if (mu < 0) {
				a = -a;
				mu = -mu;
			}
			if (mu == 1) printf("%d", a);
			else {
				printf("%d/%d", a, mu);
			}
			printf(" ");
			printf("%d", b + 1);
			printf("%c", i == n - 1 ? '\n' : ' ');
		}
	}
	return 0;
}

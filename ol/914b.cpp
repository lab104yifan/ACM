#include <cstdio>
#include <cstring>

const int N = 100005;

int n;
long long a, sum;

int main() {
	while (~scanf("%d", &n)) {
		sum = 0;
		for (int i = 0 ; i < n; i++) {
			scanf("%I64d", &a);
			sum ^= a;
		}
		if (sum == 0) printf("Lose\n");
		else printf("Win\n");
	}
	return 0;
}

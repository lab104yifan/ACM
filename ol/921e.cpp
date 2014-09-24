#include <cstdio>
#include <cstring>

int t, n;
double p;

int main() {
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		double sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lf", &p);
			sum += p;
		}
		for (int i = 0; i < n; i++)
			scanf("%*d");
		printf("Case #%d: %.6lf\n", ++cas, (1 + n) / sum);
	}
	return 0;
}

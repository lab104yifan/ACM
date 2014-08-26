#include <cstdio>
#include <cstring>

const int N = 105;

int m, a[N], sum;

int main() {
    while (~scanf("%d", &m) && m) {
	sum = 0;
	for (int i = 0; i < m; i++) {
	    scanf("%d", &a[i]);
	    sum ^= a[i];
	}
	int ans = 0;
	for (int i = 0; i < m; i++) {
	    int tmp = (a[i]^sum);
	    if (tmp < a[i])
		ans++;
	}
	printf("%d\n", ans);
    }
    return 0;
}

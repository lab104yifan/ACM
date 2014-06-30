#include <stdio.h>
#include <string.h>

const int N = 1005;
int n, ans[N];

void init() {
    memset(ans, -1, sizeof(ans));
    for (int i = 1; i <= 1000; i++) {
	int sum = 0;
	for (int j = 1; j <= i; j++) {
	    if (i % j == 0)
		sum += j;
	}
	if (sum <= 1000) ans[sum] = i;
    }
}

int main() {
    int cas = 0;
    init();
    while (~scanf("%d", &n) && n) {
	printf("Case %d: %d\n", ++cas, ans[n]);
    }
    return 0;
}

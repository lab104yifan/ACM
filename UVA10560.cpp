#include <stdio.h>
#include <string.h>

const int N = 105;
const char fh[5] = "+-";
unsigned long long n, need[N], sum[N], w;
int k, nn = 0;

void solve(int i, unsigned long long w) {
    int flag = 1;
    while (w) {
	for (;i >= 1; i--) {
	    if (w <= sum[i] && w > sum[i - 1]) {
		printf("%llu", need[i]);
		if (w > need[i]) {
		    w -= need[i];
		    printf("%c", fh[(!flag)]);
		}
		else if (w < need[i]) {
		    w = need[i] - w;
		    printf("%c", fh[flag]);
		    flag = (!flag);
		}
		else w = 0;
		i--;
		break;
	    }
	}
    }
    printf("\n");
}

int main() {
    unsigned long long Max = (1ULL<<63), now = 0;
    while (now < Max) {
	nn++;
	now = sum[nn - 1] * 2 + 1;
	sum[nn] = sum[nn - 1] + now;
	need[nn] = now;
    }
    need[++nn] = (1ULL<<64) - 1;
    sum[nn] = need[nn];
    while (~scanf("%llu%d", &n, &k) && n || k) {
	int i = 1;
	for (; i <= nn; i++) {
	    if (n <= sum[i]) break;
	}
	printf("%d", i);
	for (int j = 1; j <= i; j++)
	    printf(" %llu", need[j]);
	printf("\n");
	while (k--) {
	    scanf("%llu", &w);
	    solve(i, w);
	}
    }
    return 0;    
}

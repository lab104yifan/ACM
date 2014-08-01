#include <stdio.h>
#include <string.h>

const long long N = 1000005;

bool ispri[N * 3];
int ans[N], t, n;

int main() {
    for (long long i = 2; i < N * 3; i++) {
	if (ispri[i]) continue;
	for (long long j = i * i; j < N * 3; j += i)
	    ispri[j] = true;
    }
    for (int i = 2; i < N; i++)
	ans[i] = ans[i - 1] + (!ispri[3 * i + 7]);
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	printf("%d\n", ans[n]);
    }
    return 0;
}

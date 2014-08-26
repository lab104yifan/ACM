#include <cstdio>
#include <cstring>

int n, num[100];

int main() {
    while (~scanf("%d", &n)) {
	int ans = 0;
	for (int i = 0; i < n; i++)
	    scanf("%d", &num[i]);
	for (int i = 0; i < (1<<n); i++) {
	    int sum = 0;
	    for (int j = 0; j < n; j++) {
		if (i&(1<<j)) {
		    sum += num[j];
		}
	    }
	    if (sum >= 2048) ans++;
	}
	printf("%d\n", ans);
    }
    return 0;
}

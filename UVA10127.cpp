#include <stdio.h>
#include <string.h>

int n;

int main() {
    while (~scanf("%d", &n)) {
	int ans = 1;
	int now = 1;
	while (now) {
	    now = (now * 10 + 1) % n;
	    ans++;
	}
	printf("%d\n", ans);
    }
    return 0;
}

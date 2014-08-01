#include <stdio.h>
#include <string.h>

int t, n, mi;

bool judge(int num) {
    long long sb = (long long)num * num;
    if (sb % (mi * 10) == num) return true;
    return false;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	mi = 1;
	for (int i = 1; i < n; i++)
	    mi *= 10;
	printf("Case #%d:", ++cas);
	if (mi == 1) printf(" 0");
	for (int i = mi; i < mi * 10; i++) {
	    if (judge(i)) printf(" %d", i);
	}
	printf("\n");
    }
    return 0;
}

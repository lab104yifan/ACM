#include <stdio.h>
#include <string.h>

int t, n;
char a[505], b[505];
int ans[505], num[505];

int cal(char *str) {
    memset(ans, 0, sizeof(ans));
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--)
	num[len - i - 1] = str[i] - '0';
    for (int i = 0; i < len; i++) {
	for (int j = 0; j < len; j++) {
	    if (i + j > len) continue;
	    ans[i + j] += num[i] * num[j];
	}
    }
    for (int i = 0; i < len; i++) {
	ans[i + 1] += ans[i] / 10;
	ans[i] %= 10;
    }
    return ans[len];
}

void init() {
    a[500] = '\0'; b[500] = '\0';
    a[499] = '5'; b[499] = '6';
    for (int i = 498; i >= 0; i--) {
	int aa = cal(a + i + 1);
	int bb = cal(b + i + 1);
	for (int j = 0; j < 10; j++) {
	    if ((2 * j * 5 + aa) % 10 == j)
		a[i] = j + '0';
	    if ((2 * j * 6 + bb) % 10 == j)
		b[i] = j + '0';
	}
    }
}

int main() {
    init();
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	printf("Case #%d:", ++cas);
	if (n == 1) printf(" 0 1 5 6\n");
	else {
	    if (a[500 - n] == '0' && b[500 - n] == '0') printf("Impossible\n");
	    else if (a[500 - n] == '0') printf(" %s\n", b + 500 - n);
	    else if (b[500 - n] == '0') printf(" %s\n", a + 500 - n);
	    else {
		if (strcmp(a + 500 - n, b + 500 - n) < 0) printf(" %s %s\n", a + 500 - n, b + 500 - n);
		else printf(" %s %s\n", b + 500 - n, a + 500 - n);
	    }
	}
    }
    return 0;
}

#include <cstdio>
#include <cstring>

const int N = 1000005;

int n, next[N];
char str[N];

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	scanf("%s", str + 1);
	next[1] = 0;
	int j = 0;
	for (int i = 2; i <= n; i++) {
	    while (j && str[i] != str[j + 1]) j = next[j];
	    if (str[i] == str[j + 1]) j++;
	    next[i] = j;
	}
	printf("Test case #%d\n", ++cas);
	for (int i = 1; i <= n; i++) {
	    if (!next[i]) continue;
	    if (i % (i - next[i])) continue;
	    printf("%d %d\n", i, i / (i - next[i]));
	}
	printf("\n");
    }
    return 0;
}

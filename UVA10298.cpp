#include <cstdio>
#include <cstring>

const int N = 1000005;
char str[N];
int next[N];

void getnext() {
    int n = strlen(str);
    next[0] = next[1] = 0;
    int j = 0;
    for (int i = 2; i <= n; i++) {
	while (j && str[i - 1] != str[j]) j = next[j];
	if (str[i - 1] == str[j]) j++;
	next[i] = j;
    }
    printf("%d\n", n / (n - next[n]));
}

int main() {
    while (~scanf("%s", str) && strcmp(str, ".") != 0) {
	getnext();
    }
    return 0;
}

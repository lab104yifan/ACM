#include <cstdio>
#include <cstring>

const int N = 10005;

int t;
char str[N];

int solve(char *str) {
    int i, j, l, n = strlen(str);
    i = 0; j = 1;
    while (i < n && j < n) {
	for (l = 0; l < n; l++)
	    if (str[(i + l) % n] != str[(j + l) % n]) break;
	if (l >= n) break;
	if (str[(i + l) % n] > str[(j + l) % n])
	    i = i + l + 1;
	else
	    j = j + l + 1;
	if (i == j) j = i + 1;
    }
    if (i < j) return i;
    return j;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%s", str);
	printf("%d\n", solve(str) + 1);
    }
    return 0;
}

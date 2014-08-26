#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXLEN = 100005;

struct KMP {

    int next[MAXLEN];

    void getnext(char *str) {
	int n = strlen(str);
	next[1] = 0;
	int j = 0;
	for (int i = 2; i <= n; i++) {
	    while (j && str[j] != str[i - 1]) j = next[j];
	    if (str[j] == str[i - 1]) j++;
	    next[i] = j;
	}
    }

    void find(char *T, char *s) {
	int n = strlen(T);
	getnext(s);
	int j = 0;
	for (int i = 0; i < n; i++) {
	    while (j && T[i] != s[j]) j = next[j];
	    if (T[i] == s[j]) j++;
	}
	printf("%s%s\n", T, s + j);
    }
};

KMP gao;
char a[MAXLEN], b[MAXLEN];

int main() {
    while (~scanf("%s", a)) {
	strcpy(b, a);
	reverse(b, b + strlen(b));
	gao.find(a, b);
    }
    return 0;
}

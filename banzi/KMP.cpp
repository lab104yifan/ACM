#include <cstdio>
#include <cstring>

const int MAXLEN = 10005;

struct KMP {

    int next[MAXLEN];

    void init() {}

    void getnext(char *P) {
	next[0] = next[1] = 0;
	int n = strlen(P), j = 0;
	for (int i = 2; i <= n; i++) {
	    while (j && P[i - 1] != P[j]) j = next[j];
	    if (P[i - 1] == P[j]) j++;
	    next[i] = j;
	}
    }

    void getnext2(char *str) {
	next[0] = -1;
	int j = -1;
	for (int i = 1; i < n; i++) {
	    while (j >= 0 && str[i] != str[j + 1]) j = next[j];
	    if (str[i] == str[j + 1]) j++;
	    next[i] = j;
	}
    }

    void find(char *T, char *P) {
	int n = strlen(T), m = strlen(P), j = 0;
	getnext(P);
	for (int i = 0; i < n; i++) {
	    while (j && T[i] != P[j]) j = next[j];
	    if (T[i] == P[j]) j++;
	    if (j == m) {
		//write
	    }
	}
    }
};

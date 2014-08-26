#include <cstdio>
#include <cstring>

const int MAXNODE = 1000005;
const int SIGMA_SIZE = 26;

struct Trie {

    int ch[MAXNODE][SIGMA_SIZE];
    int val[MAXNODE];
    int sz;

    void init() {
	sz = 1; 
	memset(ch[0], 0, sizeof(ch[0]));
    }

    int idx(char c) {return c - 'a';}

    void insert(char *str, int v) {
	int n = strlen(str);
	int u = 0;
	for (int i = 0; i < n; i++) {
	    int c = idx(str[i]);
	    if (!ch[u][c]) {
		memset(ch[sz], 0, sizeof(ch[sz]));
		val[sz] = 0;
		ch[u][c] = sz++;
	    }
	    u = ch[u][c];
	}
	val[u] = v;
    }
} gao;

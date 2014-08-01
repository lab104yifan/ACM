#include <cstdio>
#include <cstring>

const int MAXNODE = 11000;

struct Trie {
    
    int val[MAXNODE];
    char ch[MAXNODE];
    int sz;
    int first[MAXNODE], next[MAXNODE];

    void init() {sz = 1; val[0] = 0; first[0] = 0;}
    
    int idx(char c) {return c - 'a';}
    
    void insert(char *str) {
	int n = strlen(str);
	int u = 0;
	int v = 0;
	for (int i = 0; i <= n; i++) {
	    bool flag = true;
	    for (v = first[u]; v; v = next[v]) {
		if (ch[v] == str[i]) {
		    flag = false;
		    break;
		}
	    }
	    if (flag) {
		v = sz++;
		first[v] = 0;
		ch[v] = str[i];
		val[v] = 0;
		next[v] = first[u];
		first[u] = v;
	    }
	    u = v;
	    val[u]++;
	}
    }
};

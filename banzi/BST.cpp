#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXNODE = 1111111;

struct BST {
    struct Node {
	int l, r, val, lsz, rsz;
	Node() {l = 0, r = 0, val = -1; lsz = 0; rsz = 0;}
    } node[MAXNODE];

    int sz;

    void init() {
	node[1] = Node();
	sz = 2;
    }

    void insert(int v, int x = 1) {
	if (node[x].val == -1) {
	    node[x].val = v;
	    return;
	}
	if (v < node[x].val) {
	    if (!node[x].l) {
		node[sz] = Node();
		node[x].l = sz++;
	    }
	    insert(v, node[x].l);
	    node[x].lsz++;
	}
	else {
	    if (!node[x].r) {
		node[sz] = Node();
		node[x].r = sz++;
	    }
	    insert(v, node[x].r);
	    node[x].rsz++;
	}
    }
} gao;

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

struct SplayTree {

    struct Node {

	Node *ch[2];
	int v, s;
	int flip;
	
	Node() {}
	Node(int v) {
	    ch[0] = ch[1] = NULL; 
	    this->v = v; s = 1; flip = 0;
	}

	int cmp(int x) const {
	    if (x == v) return -1;
	    return x < v ? 0 : 1;
	}

	void maintain() {
	    s = 1;
	    if (ch[0] != NULL) s += ch[0]->s;
	    if (ch[1] != NULL) s += ch[1]->s;
	}

	void pushdown() {
	    if (flip) {
		flip = 0;
		swap(ch[0], ch[1]);
		ch[0]->flip = !ch[0]->flip;
		ch[1]->flip = !ch[1]->flip;
	    }
	}
    };

    Node *null;

    //0 is left, 1 is right
    void rotate(Node* &o, int d) {
	Node *k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
	o->maintain(); k->maintain(); o = k;
    }

    void splay(Node * &o, int k) {
	o->pushdown();
	int d = o->cmp(k);
	if (d == 1) k -= o->ch[0]->s + 1;
	if (d != -1) {
	    Node *p = p->ch[d];
	    p->pushdown();
	    int d2 = p->cmp(k);
	    int k2 = (d2 == 0 ? k : k - p->ch[0]->s - 1);
	    if (d2 != -1) {
		splay(p->ch[d2], k2);
		if (d == d2) rotate(o, d^1);
		else rotate(o->ch[d], d);
	    }
	    rotate(o, d^1);
	}
    }

    Node *merge(Node *left, Node *right) {
	splay(left, left->s);
	left->ch[1] = right;
	left->maintain();
	return left;
    }

    void split(Node *o, int k, Node* &left, Node* &right) {
	splay(o, k);
	left = o;
	right = o->ch[1];
	o->ch[1] = null;
	left->maintain();
    }

    bool isexist(Node *o, int x) {
	while (o != NULL) {
	    int d = o->cmp(x);
	    if (d == -1) return true;
	    else o = o->ch[d];
	}
	return false;
    }

    int findkth(Node *o, int k, int flag) { //1 is bigth, 0 is smallth
	if (o == NULL || k <= 0 || k > o->s) return 0;
	int s = (o->ch[flag] == NULL ? 0 : o->ch[flag]->s);
	if (k == s + 1) return o->v;
	else if (k <= s) return findkth(o->ch[flag], k, flag);
	else return findkth(o->ch[flag^1], k - s - 1, flag);
    }

    void removetree(Node* &x) {
	if (x == NULL) return;
	if (x->ch[0] != NULL) removetree(x->ch[0]);
	if (x->ch[1] != NULL) removetree(x->ch[1]);
	delete x; x = NULL;
    }

    void init() {
	null = new Node(0);
    }

    void build(Node* &o, int l, int r) {
	int mid = (l + r) / 2;
	o = new node(mid);
	if (l < mid) build(o->ch[0], l, m - 1);
	if (r > m) build(o->ch[1], m + 1, r);
	o->maintain();
    }

    int n, m;
    Node *root;

    void solve() {
	init();
	build(root, 0, n + 1);
	int a, b;
	Node *left, *mid, *right, *o;
	while (m--) {
	    scanf("%d%d", &a, &b);
	    split(root, a, left, o);
	    split(o, b - a + 1, mid, right);
	    mid->flip ^= 1;
	    root = merge(merge(left, right), mid);
	}
    }
} gao;

int main() {
    while (~scanf("%d%d", &gao.n, &gao.m)) {
	gao.solve();
    }
    return 0;
}

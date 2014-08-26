#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

struct Treap {

    struct Node {

	Node *ch[2];
	int r, v, s;
	
	Node() {}
	Node(int v) {ch[0] = ch[1] = NULL; r = rand(); this->v = v; s = 1;}
	bool operator < (const Node& c) const {
	    return r < c.r;
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
    };

    //0 is left, 1 is right
    void rotate(Node* &o, int d) {
	Node *k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
	o->maintain(); k->maintain(); o = k;
    }

    void insert(Node* &o, int x) {
	if (o == NULL) o = new Node(x);
	else {
	    int d = (x < o->v ? 0 : 1);
	    insert(o->ch[d], x);
	    if (o->ch[d]->r > o->r) rotate(o, d^1);
	}
	o->maintain();
    }

    void remove(Node* &o, int x) {
	int d = o->cmp(x);
	if (d == -1) {
	    Node* u = o;
	    if (o->ch[0] != NULL && o->ch[1] != NULL) {
		int d = o->ch[0]->r > o->ch[1]->r ? 1 : 0;
		rotate(o, d); remove(o->ch[d], x);
	    } else {
		if (o->ch[0] == NULL) o = o->ch[1];
		else o = o->ch[0];
		delete u; u = NULL;
	    }

	} else
	    remove(o->ch[d], x);
	if (o != NULL) o->maintain();
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

    void mergeto(Node* &a, Node* &b) {//a mergeto b
	if (a->ch[0] != NULL) mergeto(a->ch[0], b);
	if (a->ch[1] != NULL) mergeto(a->ch[1], b);
	insert(b, a->v);
	delete a; a = NULL;
    }

    void removetree(Node* &x) {
	if (x == NULL) return;
	if (x->ch[0] != NULL) removetree(x->ch[0]);
	if (x->ch[1] != NULL) removetree(x->ch[1]);
	delete x; x = NULL;
    }
} gao;

int main() {
    return 0;
}

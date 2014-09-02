#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100005;

struct SplayTree {

	struct Node {

		Node *ch[2];
		int v, s;
		int flip;

		Node() {
			ch[0] = ch[1] = NULL;
			v = s = flip = 0;
		}
		Node(int v) {
			ch[0] = ch[1] = NULL; 
			this->v = v; s = 1; flip = 0;
		}

		int cmp(int x) const {
			int d = x - ch[0]->s;
			if (d == 1) return -1;
			return d <= 0 ? 0 : 1;
		}

		void maintain() {
			s = ch[0]->s + ch[1]->s + 1;
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
			Node *p = o->ch[d];
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

	Node* getnext(Node *o, int k) {
		if (o == null) return null;
		pushdown(o);
		if (o->v == k) return o;
		else if (o->v < k) return find(o->ch[1], k);
		else {
			Node* tmp = find(o->ch[0], k);
			if (tmp == null) return o;
			else return tmp;
		}
	}

	Node* getpre(Node *o, int k) {
		if (o == null) return null;
		pushdown(o);
		if (o->v == k) return o;
		else if (o->v > k) return find(o->ch[0], k);
		else {
			Node *tmp = find(o->ch[1], k);
			if (tmp == null) return o;
			else return tmp;
		}
	}

	Node* findkth(Node *o, int k) {
		if (o == null || k <= 0 || k > o->s) return 0;
		pushdown(o);
		int s = (o->ch[0] == null ? 0 : o->ch[0]->s);
		if (k == s + 1) return o;
		else if (k <= s) return findkth(o->ch[0], k);
		else return findkth(o->ch[1], k - s - 1);
	}

	Node* merge(Node *left, Node *right) {
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

	void rever(Node* &root, int l, int r) {
		Node *left, *mid, *right, *o;
		split(root, l, left, o);
		split(o, r - l + 1, mid, right);
		mid->flip ^= 1;
		root = merge(merge(left, right), mid);
	}

	void removetree(Node* &x) {
		if (x == NULL) return;
		if (x->ch[0] != NULL) removetree(x->ch[0]);
		if (x->ch[1] != NULL) removetree(x->ch[1]);
		delete x; x = NULL;
	}

	void build(Node* &o, int l, int r) {
		if (l > r) {
			o = null;
			return;
		}
		int mid = (l + r) / 2;
		o = new Node(mid);
		build(o->ch[0], l, mid - 1);
		build(o->ch[1], mid + 1, r);
		o->maintain();
	}

	Node* root;

	struct Arr {
		int val, id;
		bool operator < (const Arr& c) const {
			if (val != c.val) return val < c.val;
			return id < c.id;
		}
	} num[N];

	void init() {
		removetree(root);
		null = new Node();
	}

	void solve() {
		init();
		build(root, 0, n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &num[i].val);
			num[i].id = id;
		}
		sort(num + 1, num + 1 + n, cmp);
		for (int i = 1; i <= n; i++) {
		}
	}
} gao;

int main() {

	return 0;
}

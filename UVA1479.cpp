#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 500005;
const int N = 20005;
const int M = 60005;
int cas = 0;

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

    int find(int x) {
	return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    Node* root[N];

    int n, m, query_num;
    int weight[N], parent[N], vis[M];
    ll query_tot;

    struct Query {
	int type, x, v;
	Query() {}
	Query(int type, int x, int v) {
	    this->type = type;
	    this->x = x;
	    this->v = v;
	}
    } Q[MAXN];

    int qn;

    struct Edge {
	int u, v;
	Edge() {}
	Edge(int u, int v) {
	    this->u = u;
	    this->v = v;
	}
	void read() {
	    scanf("%d%d", &u, &v);
	}
    } E[M];

    void add_edge(Edge x) {
	int pu = find(x.u), pv = find(x.v);
	if (pu != pv) {
	    if (root[pu]->s > root[pv]->s)
		swap(pu, pv);
	    parent[pu] = pv;
	    mergeto(root[pu], root[pv]);
	}
    }

    void init() {
	
	query_num = 0;
	query_tot = 0;
	
	for (int i = 1; i <= n; i++) {
	    scanf("%d", &weight[i]);
	    parent[i] = i;
	    removetree(root[i]);
	}
	for (int i = 1; i <= m; i++)
	    E[i].read();

	char C[10]; int a, b; qn = 0;
	memset(vis, 0, sizeof(vis));
	
	while (scanf("%s", C) && C[0] != 'E') {
	    if (C[0] == 'D') {
		scanf("%d", &a);
		vis[a] = 1;
		Q[qn++] = Query(0, a, 0);
	    }
	    else {
		scanf("%d%d", &a, &b);
		if (C[0] == 'C') {
		    int tmp = weight[a];
		    weight[a] = b;
		    b = tmp;
		    Q[qn++] = Query(1, a, b);
		}
		else Q[qn++] = Query(2, a, b);
	    }
	}

	for (int i = 1; i <= n; i++)
	    insert(root[i], weight[i]);
	for (int i = 1; i <= m; i++) {
	    if (vis[i]) continue;
	    add_edge(E[i]);
	}
    }

    void solve() {
	init();
	for (int i = qn - 1; i >= 0; i--) {
	    if (Q[i].type == 0)
		add_edge(E[Q[i].x]);
	    else if (Q[i].type == 1) {
		int pu = find(Q[i].x);
		if (isexist(root[pu], weight[Q[i].x]))
		    remove(root[pu], weight[Q[i].x]);
		insert(root[pu], Q[i].v);
		weight[Q[i].x] = Q[i].v;
	    } else {
		int pu = find(Q[i].x);
		query_num++;
		query_tot += findkth(root[pu], Q[i].v, 1);
		//printf("%d %lld\n", query_num, query_tot);
	    }
	}
	printf("Case %d: %.6lf\n", ++cas, query_tot * 1.0 / query_num);
    }

} gao;

int main() {
    while (~scanf("%d%d", &gao.n, &gao.m) && gao.n || gao.m) {
	gao.solve();
    }
    return 0;
}

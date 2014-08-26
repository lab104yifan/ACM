#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int SIGMA_SIZE = 2;

struct Node {
    Node *ch[2];
    int val;
    Node() {
	ch[0] = ch[1] = NULL;
	val = 0;
    }
};

struct Trie {
    
    Node *root;
    int ans;

    int idx(char c) {
	return c - '0';
    }

    void init() {
	ans = 0;
	root = new Node();
    }

    void insert(char *s) {
	int n = strlen(s);
	Node *u = root;
	for (int i = 0; i < n; i++) {
	    int c = idx(s[i]);
	    if (u->ch[c] == NULL) {
		u->ch[c] = new Node();
	    }
	    u = u->ch[c];
	    u->val++;
	}
    }
    
    void dfs(Node *u, int d) {
	if (u == NULL) return;
	ans = max(ans, d * u->val);
	for (int c = 0; c < SIGMA_SIZE; c++)
	    dfs(u->ch[c], d + 1);
    }

    void del(Node *u) {
	if (u == NULL) return;
	for (int c = 0; c < SIGMA_SIZE; c++)
	    del(u->ch[c]);
	delete u;
    }

    int solve() {
	dfs(root, 0);
	del(root);
	return ans;
    }
};

Trie gao;
int t, n;
char str[205];

int main() {
    scanf("%d", &t);
    while (t--) {
	gao.init();
	scanf("%d", &n);	
	while (n--) {
	    scanf("%s", str);
	    gao.insert(str);
	}
	printf("%d\n", gao.solve());
    }
    return 0;
}

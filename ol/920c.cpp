#include <cstdio>
#include <cstring>

#define lson(x) ((x<<1)+1)
#define rson(x) ((x<<1)+2)

const int N = 1000005;

int n, q;

struct Node {
	int l, r, color, c;
	Node() {}
	Node(int l, int r, int color, int c) {
		this->l = l;
		this->r = r;
		this->color = color;
		this->c = c;
	}
} node[4 * N];

void build(int l, int r, int x = 0) {
	node[x] = Node(l, r, 2, 0);
	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(l, mid, lson(x));
	build(mid + 1, r, rson(x));
}

void pushup(int x) {
	node[x].color = (node[lson(x)].color | node[rson(x)].color);
}

void pushdown(int x) {
	if (node[x].c == 0) return;
	node[lson(x)].color = (1<<(node[x].c - 1));
	node[rson(x)].color = (1<<(node[x].c - 1));
	node[lson(x)].c = node[x].c;
	node[rson(x)].c = node[x].c;
	node[x].c = 0;
}

void add(int l, int r, int c, int x = 0) {
	if (node[x].l >= l && node[x].r <= r) {
		node[x].c = c;
		node[x].color = (1<<(c - 1));
		return;
	}
	pushdown(x);
	int mid = (node[x].l + node[x].r) / 2;
	if (l <= mid) add(l, r, c, lson(x));
	if (r > mid) add(l, r, c, rson(x));
	pushup(x);
}

int query(int l, int r, int x = 0) {
	if (node[x].l >= l && node[x].r <= r) {
		return node[x].color;
	}
	pushdown(x);
	int mid = (node[x].l + node[x].r) / 2;
	int ans = 0;
	if (l <= mid) ans |= query(l, r, lson(x));
	if (r > mid) ans |= query(l, r, rson(x));
	pushup(x);
	return ans;
}

int main() {
	while (~scanf("%d%d", &n, &q) && n || q) {
		build(1, n);
		char s[2];
		while (q--) {
			scanf("%s", s);
			int l, r, c;
			if (s[0] == 'P') {
				scanf("%d%d%d", &l, &r, &c);
				add(l, r, c);
			} else {
				scanf("%d%d", &l, &r);
				int tmp = query(l, r);
				int bo = 0;
				for (int i = 0; i < 30; i++) {
					if (tmp&(1<<i)) {
						if (bo) printf(" ");
						else bo = 1;
						printf("%d", i + 1);
					}
				}
				printf("\n");
			}
		}
	}
	return 0;
}

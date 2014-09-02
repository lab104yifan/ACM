struct Graph {

	struct Edge {
		int u, v, val, next;
		Edge() {}
		Edge(int u, int v, int val = 0) {
			this->u = u;
			this->v = v;
			this->val = val;
		}
	} edge[MAXN];

	int first[N], en;

	void init() {
		memset(first, -1, sizeof(first));
		en = 0;
	}
	void add(int u, int v, int val = 0) {
		edge[en] = Edge(u, v, val);
		edge[en].next = first[u];
		first[u] = en++;
	}
} g;

bool dfs(int u) {
	for (int i = g.first[u]; i != -1; i = g.edge[i].next) {
		int v = g.edge[i].v;
		if (vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

bool hungary() {
	int sum = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < 2 * b; i++) {
		memset(vis, 0, sizeof(vis));
		if (!dfs(i)) return false;
	}
	return true;
}

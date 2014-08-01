#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

int n, m;

map<int, vector<int> > ans;

int main() {
    while (~scanf("%d%d", &n, &m)) {
	int a, b;
	ans.clear();
	for (int i = 1; i <= n; i++) {
	    scanf("%d", &a);
	    if (!ans.count(a)) ans[a] = vector<int> ();
	    ans[a].push_back(i);
	}
	while (m--) {
	    scanf("%d%d", &a, &b);
	    if (ans[b].size() < a) printf("0\n");
	    else printf("%d\n", ans[b][a - 1]);
	}
    }
    return 0;
}

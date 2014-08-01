#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n, m;
struct Num {
    int v, num;
    Num() {}
    Num(int v, int num) {
	this->v = v;
	this->num = num;
    }
};

vector<vector<Num> > g;
vector<int> tmp;

int main() {
    while (~scanf("%d%d", &n, &m)) {
	g.clear();
	for (int i = 0; i < m; i++)
	    g.push_back(vector<Num>());
	int k;
	for (int i = 0; i < n; i++) {
	    scanf("%d", &k);
	    int v, num;
	    tmp.clear();
	    for (int j = 0; j < k; j++) {
		scanf("%d", &v);
		v--;
		tmp.push_back(v);
	    }
	    for (int j = 0; j < k; j++) {
		scanf("%d", &num);
		g[tmp[j]].push_back(Num(i ,num));
	    }
	}
	printf("%d %d\n", m, n);
	for (int i = 0; i < m; i++) {
	    int sz = g[i].size();
	    printf("%d", sz);
	    for (int j = 0; j < sz; j++)
		printf(" %d", g[i][j].v + 1);
	    printf("\n");
	    for (int j = 0; j < sz; j++) {
		printf("%d%c", g[i][j].num, j == sz - 1 ? '\n' : ' ');
	    }
	    if (sz == 0) printf("\n");
	}
    }
    return 0;
}

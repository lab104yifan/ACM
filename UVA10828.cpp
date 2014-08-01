#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const int N = 105;
const double eps = 1e-9;
int n, d[N], inf[N];
double a[N][N];
vector<int> pre[N];

void build() {
    int u, v;
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++)
	pre[i].clear();
    while (~scanf("%d%d", &u, &v) && u) {
	u--; v--; d[u]++;
	pre[v].push_back(u);
    }
    memset(a, 0, sizeof(a));
    for (int i = 0; i < n; i++) {
	a[i][i] = 1;
	for (int j = 0; j < pre[i].size(); j++)
	    a[i][pre[i][j]] = -1.0 / d[pre[i][j]];
	if (i == 0) a[i][n] = 1;
    }
}

void gauss() {
    for (int i = 0; i < n; i++) {
	int k = i;
	for (;k < n; k++)
	    if (fabs(a[k][i]) > eps) break;
	if (k == n) continue;
	for (int j = 0; j <= n; j++) swap(a[k][j], a[i][j]);
	for (int j = 0; j < n; j++) {
	    if (i == j) continue;
	    if (fabs(a[k][i]) > eps) {
		double x = a[j][i] / a[i][i];
		for (int k = i; k <= n; k++)
		    a[j][k] -= x * a[i][k];
	    }
	}
    }
}

void get_inf() {
    memset(inf, 0, sizeof(inf));
    for (int i = n - 1; i >= 0; i--) {
	if (fabs(a[i][i]) < eps && fabs(a[i][n]) > eps) inf[i] = 1;
	for (int j = i + 1; j < n; j++)
	    if (fabs(a[i][j]) > eps && inf[j]) inf[i] = 1;
    }
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	build();
	gauss();
	get_inf();
	int q, node;
	scanf("%d", &q);
	printf("Case #%d:\n", ++cas);
	while (q--) {
	    scanf("%d", &node);
	    node--;
	    if (inf[node]) printf("infinity\n");
	    else printf("%.3lf\n", fabs(a[node][node]) < eps ? 0 : a[node][n] / a[node][node]);
	}
    }
    return 0;
}

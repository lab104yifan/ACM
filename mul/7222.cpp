#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-9;
const int N = 305;

double p, a[N][N];
int mark[25][25];

double solve() {
    for (int i = 0; i < 210; i ++) {
	int k = i;
	for (; k < 210; k++)
	    if (fabs(a[k][i]) > eps) break;
	for (int j = 0; j <= 210; j++)
	    swap(a[i][j], a[k][j]);
	for (int j = 0; j < 210; j++) {
	    if (i == j) continue;
	    if (fabs(a[j][i]) > eps) {
		double x = a[j][i] / a[i][i];
		for (int k = i; k <= 210; k++) {
		    a[j][k] -= a[i][k] * x;
		}
	    }
	}
    }
    return a[0][210] / a[0][0];
}

void build() {
    memset(a, 0, sizeof(a));
    for (int i = 0; i < 20; i++) {
	for (int j = 0; j < i; j++) {
	    int u = mark[i][j];
	    a[u][u] = 1;
	    a[u][210] = 1;
	    int v = mark[i][max(0, j - 2)];
	    a[u][v] -= (1 - p);
	    v = mark[i][j + 1];
	    a[u][v] -= p;
	}
	int u = mark[i][i];
	a[u][u] = 1;
	a[u][210] = 1;
	int v = mark[i][max(0, i - 2)];
	a[u][v] -= (1 - p);
	v = mark[i + 1][i];
	a[u][v] -= p;
    }
}

int main() {
    int cnt = 0;
    memset(mark, -1, sizeof(mark));
    for (int i = 0; i < 20; i++) {
	for (int j = 0; j <= i; j++) {
	    mark[i][j] = cnt;
	    cnt++;
	}
    }
    while (~scanf("%lf", &p)) {
	build();
	printf("%.6lf\n", solve());
    }
    return 0;
}

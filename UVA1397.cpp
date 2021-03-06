#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 25;
const double eps = 1e-9;

ll a, m, b, n, C[N][N];
int hash[N][N], tot;

double A[N][N];

void build() {
    memset(A, 0, sizeof(A));
    A[0][0] = 1;
    for (int i = 1; i <= tot; i++) {
	for (int j = 0; j <= i; j++) {
	    int l = j, r = i - j;
	    double tmp = C[i][l] * pow(a * 1.0, l / m) * pow(b * 1.0, r / n);
	    l %= m; r %= n;
	    A[hash[l][r]][i] += tmp;
	}
    }
    A[tot][tot] = 1;
    A[tot][tot + 1] = 1;
    tot++;
}

void getC() {
    for (int i = 0; i <= 20; i++) {
	C[i][0] = C[i][i] = 1;
	for (int j = 1; j < i; j++)
	    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

void gethash() {
    tot = 0;
    for (int i = 0; i < m; i++) {
	for (int j = 0; j < n; j++) {
	    hash[i][j] = tot++;
	}
    }
}

void print(double x) {
    char s[100];
    sprintf(s, "%.0lf", x);
    if (strcmp(s, "-0") == 0) printf(" %s", s + 1);
    else printf(" %s", s);
}

void gauss() {
    for (int i = 0; i < tot; i++) {
	int r = i;
	for (int j = i + 1; j < tot; j++) {
	    if (fabs(A[j][i]) > fabs(A[r][i]))
		r = j;
	}
	if (fabs(A[r][i]) < eps) continue;
	for (int j = i; j <= tot; j++)
	    swap(A[r][j], A[i][j]);
	for (int j = 0; j < tot; j++) {
	    if (i == j) continue;
	    if (fabs(A[j][i]) >= eps) {
		double tmp = A[j][i] / A[i][i];
		for (int k = i; k <= tot; k++)
		    A[j][k] -= tmp * A[i][k];
	    }
	}
    }
    printf("1");
    for (int i = tot - 2; i >= 0; i--)
	print(A[i][tot] / A[i][i]);
    printf("\n");
}

int main() {
    getC();
    while (~scanf("%lld%lld%lld%lld", &a, &m, &b, &n)) {
	if (!a && !m && !b && !n) break;
	gethash();
	build();
	gauss();
    }
    return 0;
}

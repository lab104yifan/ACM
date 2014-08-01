#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-9;
const int N = 105;

int n = 0;
char str[100005];

struct GaussNum {
    double a, b;
    GaussNum() {}
    GaussNum(double a, double b) {
	this->a = a; this->b = b;
    }
    GaussNum operator + (GaussNum c) {
	GaussNum ans;
	ans.a = a + c.a;
	ans.b = b + c.b;
	return ans;
    }
    GaussNum operator - (GaussNum c) {
	GaussNum ans;
	ans.a = a - c.a;
	ans.b = b - c.b;
	return ans;
    }
    GaussNum operator * (GaussNum c) {
	GaussNum ans;
	ans.a = a * c.a - b * c.b;
	ans.b = a * c.b + b * c.a;
	return ans;
    }
    GaussNum operator / (GaussNum c) {
	GaussNum ans;
	ans.a = (a * c.a + b * c.b) / (c.a * c.a + c.b * c.b);
	ans.b = (b * c.a - a * c.b) / (c.a * c.a + c.b * c.b);
	return ans;
    }
};

GaussNum a[N][N];
long long ans[N][2];

void build(char *str) {
    int read;
    int j = 0;
    while (sscanf(str, "(%lf,%lf)%n", &a[n][j].a, &a[n][j].b, &read) != EOF) {
	str += read + 1;
	j++;
    }
}

bool gauss() {
    for (int i = 0; i < n; i++)
	a[i][n] = a[i][n] * GaussNum(10, 0);
    for (int i = 0; i < n; i++) {
	int k = i;
	for (; k < n; k++)
	    if (fabs(a[k][i].a) > eps || fabs(a[k][i].a) > eps) break;
	if (k == n) return false;
	for (int j = 0; j <= n; j++)
	    swap(a[k][j], a[i][j]);
	for (int j = 0; j < n; j++) {
	    if (i == j) continue;
	    if (fabs(a[j][i].a) > eps || fabs(a[j][i].b) > eps) {
		GaussNum x = a[j][i] / a[i][i];
		for (int k = i; k <= n; k++)
		    a[j][k] = (a[j][k] - (x * a[i][k]));
	    }
	}
    }
    for (int i = n - 1; i >= 0; i--) {
	GaussNum tmp = a[i][n] / a[i][i];
	ans[i][0] = (long long)(tmp.a + eps);
	ans[i][1] = (long long)(tmp.b + eps);
    }
    return true;
}

int main() {
    int bo = 0;
    while (gets(str)) {
	if (str[0] == '\0') {
	    if (bo++) printf("\n");
	    if (gauss()) {
		for (int i = 0; i < n; i++)
		    printf("(%lld.%lld,%lld.%lld)\n", ans[i][0] / 10, ans[i][0] % 10, ans[i][1] / 10, ans[i][1] % 10);
	    }
	    else printf("No solution\n");
	    n = 0;
	}
	else {
	    build(str);
	    n++;
	}
    }
    return 0;
}

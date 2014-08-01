#include <cstdio>
#include <cstring>

const int N = 55;

int t, n, r, a[N];

struct mat {
    int v[N][N];
    mat() {memset(v, 0, sizeof(v));}
    mat operator * (mat c) {
	mat ans;
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++)
		    ans.v[i][j] = (ans.v[i][j] + v[i][k] * c.v[k][j]) % 1000;
	    }
	}
	return ans;
    }
};

mat pow_mod(mat x, int k) {
    mat ans;
    for (int i = 0; i < n; i++) ans.v[i][i] = 1;
    while (k) {
	if (k&1) ans = ans * x;
	x = x * x;
	k >>= 1;
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &n, &r);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	int x; mat Mat;
	for (int i = 0; i < n; i++) {
	    scanf("%d", &x);
	    int b;
	    while (x--) {
		scanf("%d", &b);
		Mat.v[i][b] = 1;
	    }
	}
	Mat = pow_mod(Mat, r);
	for (int i = 0; i < n; i++) {
	    int ans = 0;
	    for (int j = 0; j < n; j++) {
		ans = (ans + a[j] * Mat.v[i][j]) % 1000;
	    }
	    printf("%d%c", ans, (i == n - 1 ? '\n' : ' '));
	}
    }
    return 0;
}

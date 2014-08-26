#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

inline void scanf_(int &num)//无负数
{
    char in;
    while((in = getchar()) > '9' || in < '0') ;
    num = in - '0';
    while(in = getchar(),in >= '0' && in <= '9')
	num *= 10,num += in - '0';
}

const int N = 805;

int n;

int a[N][N], av[N][N], an[N], b[N][N], bv[N][N], bn[N], c[N][N];

int main() {
    while (~scanf("%d", &n)) {
	int num;
	memset(an, 0, sizeof(an));
	memset(bn, 0, sizeof(bn));
	memset(c, 0, sizeof(c));
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		scanf_(num);
		num %= 3;
		if (num == 0) continue;
		av[j][an[j]] = i;
		a[j][an[j]++] = num;
	    }
	}
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++) {
		scanf_(num);
		num %= 3;
		if (num == 0) continue;
		bv[i][bn[i]] = j;
		b[i][bn[i]++] = num;
	    }
	}
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < an[i]; j++) {
		for (int k = 0; k < bn[i]; k++) {
		    int x = av[i][j], y = bv[i][k];
		    c[x][y] = (c[x][y] + a[i][j] * b[i][k]) % 3;
		}
	    }
	}
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n - 1; j++)
		printf("%d ", c[i][j]);
	    printf("%d\n", c[i][n - 1]);
	}
    }
    return 0;
}

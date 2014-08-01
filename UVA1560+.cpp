#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int d[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int t, a[31][31], out[6][6];

void back() {
    for (int i = 29; i >= 0; i--)
	out[i / 6][i % 6] = a[i][30];
}

void guess() {
    for (int i = 0; i < 30; i++) {
	int k = i;
	for (; k < 30; k++)
	    if (a[k][i]) break;
	for (int j = 0; j <= 30; j++)
	    swap(a[i][j], a[k][j]);
	for (int j = 0; j < 30; j++) {
	    if (i == j) continue;
	    if (a[j][i]) {
		for (int k = i; k <= 30; k++)
		    a[j][k] ^= a[i][k];
	    }
	}
    }
    back();
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	memset(a, 0, sizeof(a));
	for (int i = 0; i < 30; i++)
	    scanf("%d", &a[i][30]);
	for (int i = 0; i < 30; i++) {
	    int x = i / 6, y = i % 6;
	    for (int j = 0; j < 5; j++) {
		int xx = x + d[j][0];
		int yy = y + d[j][1];
		if (xx < 0 || xx >= 5 || yy < 0 || yy >= 6) continue;
		a[i][xx * 6 + yy] = 1;
	    }
	}
	guess();
	printf("PUZZLE #%d\n", ++cas);
	for (int i = 0; i < 5; i++) {
	    for (int j = 0; j < 5; j++)
		printf("%d ", out[i][j]);
	    printf("%d\n", out[i][5]);
	}
    }
    return 0;
}

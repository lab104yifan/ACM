#include <stdio.h>
#include <string.h>

const int Z2[10] = {0, 4, 8, 2 ,6};
int T[10][10], tn[10];
int Z[25];
char str[105];

int solve(int mod) {
    int len = strlen(str);
    int yu = 0;
    for (int i = 0; i < len ;i++) {
	yu = (yu * 10 + str[i] - '0') % mod;
    }
    return yu;
}

int main() {
    for (int i = 0; i < 10; i++) {
	int tmp = i;
	T[i][tn[i]++] = i;
	tmp = tmp * i % 10;
	while (tmp != i) {
	    T[i][tn[i]++] = tmp;
	    tmp = tmp * i % 10;
	}
    }
    for (int i = 1; i <= 20; i++) {
	int tmp = i % tn[i % 10] - 1;
	if (tmp < 0) tmp += tn[i % 10];
	Z[i] = (Z[i - 1] + T[i % 10][tmp]) % 10;
    
    }
    /*for (int i = 1; i <= 20; i++)
	printf("%d\n", Z[i]);
    for (int i = 0; i < 10; i++) {
	printf("%d: zhouqi %d:\n", i, tn[i]);
	for (int j = 0; j < tn[i]; j++)
	    printf("%d ", T[i][j]);
	printf("\n");
    }*/
    while (~scanf("%s", str) && str[0] != '0') {
	int yu = solve(100);
	int ans = (Z[yu % 20] + Z2[yu / 20]) % 10;
	printf("%d\n", ans);
    }
    return 0;
}

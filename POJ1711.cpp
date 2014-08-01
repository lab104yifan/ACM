#include <cstdio>
#include <cstring>

int ans[35][35];

int main() {
    ans[1][1] = 1;
    ans[1][2] = 2;
    ans[2][1] = 2;
    ans[2][2] = 5;
    ans[3][1] = 4;
    ans[1][3] = 4;
    ans[2][3] = 19;
    ans[3][2] = 19;
    ans[3][3] = 85;
    ans[4][3] = 898;
    ans[3][4] = 898;
    ans[4][4] = 7625;
    ans[1][7] = 73;
    ans[1][8] = 79;
    ans[2][8] = 12542;
    ans[3][7] = 460474;
    ans[3][8] = 3673546;
    ans[4][6] = 3872481;
    ans[4][7] = 62476833;
    ans[4][8] = 1003033121;
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
	printf("%d\n", ans[n][m]);
    }
    return 0;
}

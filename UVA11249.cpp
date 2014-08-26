#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;

int t, k, q, a, b;
int lose[N];

void init(int k) {
    memset(lose, 0, sizeof(lose));
    lose[1] = 1 + k + 1;
    lose[1 + k + 1] = 1;
    int pre = 1;
    for (int i = 2; i <= 100000; i++) {
	if (lose[i]) continue;
	int tmp = lose[pre] + i - pre + k + 1;
	if (tmp > 100000) break;
	pre = i;
	lose[i] = tmp;
	lose[tmp] = i;
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d%d", &k, &q);
	init(k);
	while (q--) {
	    scanf("%d%d", &a, &b);
	    if (a > b) swap(a, b);
	    if (lose[a] == b) printf("LOSING\n");
	    else printf("WINNING\n");
	}
	printf("\n");
    }
    return 0;
}

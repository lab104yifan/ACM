#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 755;
int k, Min[N], Min_c[N], ans[N], an;

int main() {
    while (~scanf("%d", &k)) {
	memset(Min, INF, sizeof(Min));
	memset(Min_c, INF, sizeof(Min_c));
	int sum = 0, Max_v, Max = 0;
	for (int i = 0; i < k; i++) {
	    int num;
	    for (int j = 0; j < k; j++) {
		scanf("%d", &num);
		if (num < Min[i]) {
		    Min_c[i] = Min[i];
		    Min[i] = num;
		}
		else if (num < Min_c[i]) Min_c[i] = num;
	    }
	    if (Min_c[i] - Min[i] > Max) {
		Max = Min_c[i] - Min[i];
		Max_v = i;
	    }
	    sum += Min[i];
	}
	an = 0;
	ans[an++] = sum;
	for (int i = 0; i < k; i++) {
	    if (Max_v == i) continue;
	    ans[an++] = sum - Min[i] + Min_c[i];
	}
	sort(ans, ans + an);
	for (int i = 0; i < k - 1; i++)
	    printf("%d ", ans[i]);
	printf("%d\n", ans[k - 1]);
    }
    return 0;
}

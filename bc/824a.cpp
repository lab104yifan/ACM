#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1005;

int n, a[N], sum;

int main() {
    while (~scanf("%d", &n)) {
	sum = 0;
	for (int i = 1; i <= n; i++) {
	    scanf("%d", &a[i]);
	    sum += a[i];
	}
	sort(a + 1, a + n + 1);
	if (a[(n + 1) / 2] * n > sum) printf("YES\n");
	else printf("NO\n");
    }
    return 0;
}

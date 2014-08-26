#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100005;
typedef long long ll;

int t, n;
ll a, Max, sum;

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	Max = 0;
	sum = 0;
	ll num = 0;
	for (int i = 0; i < n; i++) {
	    scanf("%I64d", &num);
	    Max = max(Max, num);
	    sum += num;
	}
	sum = (sum + 1) / 2;
	printf("Case #%d: %I64d\n", ++cas, max(sum, Max));
    }
    return 0;
}

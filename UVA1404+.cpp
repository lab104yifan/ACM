#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <math.h>
using namespace std;

const int N = 100005;
int prime[N], vis[N], pn = 0;
int t, a, b, k, s, hn;
vector<int> have;

bool judge(int num) {
    int m = sqrt(num);
    for (int i = 0; i < pn && prime[i] <= m; i++)
	if (num % prime[i] == 0) return false;
    return true;
}

int main() {
    for (int i = 2; i < N; i++) {
	if (vis[i]) continue;
	prime[pn++] = i;
	for (int j = i * 2; j < N; j += i)
	    vis[j] = 1;
    }
    scanf("%d", &t);
    while (t--) {
	hn = 0;
	scanf("%d%d%d%d", &a, &b, &k, &s);
	map<int, int> vis2;
	int head = 0, last = 0;
	long long ans = 0;
	vis2[0] = vis2[1] = 1;
	for (int i = a; i <= b; i++) {
	    if (vis2[i]) continue;
	    if (judge(i)) {
		have.push_back(i);
		last++;
		while (i - have[head] > s && head < last)
		    head++;
		if (i - have[head] == s && last - head == k) ans++;
	    }
	    for (long long j = (long long)i * i; j <= (long long)b; j += i)
		vis2[(int)j] = 1;
	}
	printf("%lld\n", ans);
    }
    return 0;
}

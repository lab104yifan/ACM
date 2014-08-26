#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int INF = 0x3f3f3f3f;
int t, n;

map<int, int> dp[2];
map<int, int>::iterator it;

int lowbit(int x) {
    return (x&(-x));
}

int solve() {
    dp[0].clear();
    int pre = 1, now = 0;
    int num;
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
	scanf("%d", &num);
	num /= 2;
	swap(pre, now);
	dp[now].clear();
	for (it = dp[pre].begin(); it != dp[pre].end(); it++) {
	    int s = it->first;
	    if (dp[now].count(s) == 0) dp[now][s] = dp[pre][s];
	    else dp[now][s] = max(dp[now][s], dp[pre][s]);
	    int next;
	    if (s % num) {
		next = num;
		if (dp[now].count(next) == 0) dp[now][next] = dp[pre][s] + num * 2;
		else dp[now][next] = max(dp[now][next], dp[pre][s] + num * 2);
	    }
	    else {
		next = s + num;
		int add = (s % lowbit(next) * 2 + num) * 2;
		if (dp[now].count(next) == 0) dp[now][next] = dp[pre][s] + add;
		else dp[now][next] = max(dp[now][next], dp[pre][s] + add);
	    }
	}
    }
    int ans = 0;
    for (it = dp[now].begin(); it != dp[now].end(); it++)
	ans = max(ans, it->second);
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	printf("%d\n", solve());
    }
    return 0;
}

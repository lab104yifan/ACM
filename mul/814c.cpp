#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MOD = 998244353;
const int N = 2049;

int n, num, cnt[N], have[N], hn, invv[100005], dp[2][N], mi[100005], m;
bool istwo[2048];

inline void scanf_(int &num)
{
    char in;
    while((in=getchar()) > '9' || in<'0') ;
    num=in-'0';
    while(in=getchar(),in>='0'&&in<='9')
        num*=10,num+=in-'0';
}

void init() {
    memset(cnt, 0, sizeof(cnt));
    hn = 0;
    m = n;
    for (int i = 0; i < n; i++) {
	scanf_(num);
	if (istwo[num]) m--;
	if (cnt[num] == 0) {
	    if (istwo[num])
		have[hn++] = num;
	}
	cnt[num]++;
    }
}

inline int inv(int x) {
    int k = MOD - 2;
    int ans = 1;
    while (k) {
	if (k&1) ans = (ll)ans * x % MOD;
	x = (ll)x * x % MOD;
	k >>= 1;
    }
    return ans;
}

inline int cal(int r, int ss) {
    int ans = (mi[r] - ss) % MOD;
    if (ans < 0) ans + MOD;
    return ans;
} 

int solve() {
    int pre = 1, now = 0;
    memset(dp[0], 0, sizeof(dp[0]));
    dp[0][0] = 1;
    double tot = 0;
    for (int i = 1, ii = 0; i <= 2048; i *= 2, ii++) {
	if (cnt[i] == 0) continue;
	swap(pre, now);
	memset(dp[now], 0, sizeof(dp[now]));
	int j = 0;
	for (; j <= 2048;) {
	    if (dp[pre][j]) {
		int C = 1;
		int ss = 0;
		int sum = j;
		for (int k = 0; k <= cnt[i]; k++) {
		    dp[now][sum] = ((ll)dp[pre][j] * C + dp[now][sum]) % MOD;
		    if (sum == 2048) {
			
		    }
		    sum += i;
		    ss = (ss + C) % MOD;
		    C = (ll)C * (cnt[i] - k) % MOD * invv[k + 1] % MOD;
		}
	    }
	    if (j == 0) j = i;
	    else j *= 2;
	}
    }
    return (ll)dp[now][2048] * mi[m] % MOD;
}

int main() {
    mi[0] = 1;
    memset(istwo, false, sizeof(istwo));
    for (int i = 1; i <= 2048; i *= 2)
	istwo[i] = true;
    for (int i = 1; i <= 100000; i++) {
	invv[i] = inv(i);
	mi[i] = mi[i - 1] * 2;
	if (mi[i] >= MOD)
	    mi[i] -= MOD;
    }
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	init();
	printf("Case #%d: %d\n", ++cas, solve());
    }
    return 0;
}

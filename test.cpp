#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

typedef long long ll;

const int N = 10005;
const ll MOD = 10007;

int n, k, tn;
ll s, t, table[N];
map<ll, int> dp[25];
void dfs(int now, int num, ll s) {
    if (num == 3) {
    table[tn++] = s;
    return;
    }
    for (int i = now; i < n; i++)
    dfs(i + 1, num + 1, s|(1LL<<i));
}

int main() {
    int cas = 0;
    while (~scanf("%d%d", &n, &k) && n || k) {
    tn = 0;
    dfs(0, 0, 0);
    char str[55];
    scanf("%s", str);
    s = t = 0;
    for (int i = 0; i < strlen(str); i++)
        s = s * 2 + str[i] - '0';
    scanf("%s", str);
    for (int i = 0; i < strlen(str); i++)
        t = t * 2 + str[i] - '0';
    s = s^t;
    for (int i = 0; i <= k; i++)
        dp[i].clear();
    dp[0][0] = 1;
    for (int i = 0; i < tn; i++) {
        for (int j = k; j >= 1; j--) {
        for (map<ll, int>::iterator it = dp[j - 1].begin(); it != dp[j - 1].end(); it++) {
            ll next = (it->first^table[i]);
            if (!dp[j].count(next)) dp[j][next] = 0;
            dp[j][next] = (dp[j][next] + it->second) % MOD;
        }
        }
    }
    printf("Case #%d: %d\n", ++cas, dp[k][s]); 
    }
    return 0;
}

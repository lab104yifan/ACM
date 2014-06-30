#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int n;
vector<int> f, g;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {x = 1; y = 0; return a;}
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int inv(int a, int n) {
    int x, y;
    exgcd(a, n, x , y);
    return (x + n) % n;
}

vector<int> pmod(vector<int> f, vector<int> g) {
    int fz = f.size(), gz = g.size();
    for (int i = 0; i < fz; i++) {
	int k = fz - i - gz;
	if (k < 0) break;
	int a = f[i] * inv(g[0], n) % n;
	for (int j = 0; j < gz; j++) {
	    int now = i + j;
	    f[now] = ((f[now] - a * g[j] % n) % n + n) % n;
	}
    }
    vector<int> ans;
    int p = -1;
    for (int i = 0; i < fz; i++) if (f[i] != 0) {p = i; break;}
    if (p >= 0) for (int i = p; i < fz; i++) ans.push_back(f[i]);
    return ans;
}

vector<int> gcd(vector<int> f, vector<int> g) {
    if (g.size() == 0) return f;
    return gcd(g, pmod(f, g));
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	f.clear(); g.clear();
	int a, k;
	scanf("%d", &a);
	for (int i = 0; i <= a; i++) {
	    scanf("%d", &k);
	    f.push_back(k);
	}
	scanf("%d", &a);
	for (int i = 0; i <= a; i++) {
	    scanf("%d", &k);
	    g.push_back(k);
	}
	vector<int> ans = gcd(f, g);
	int tmp = inv(ans[0], n), ansz = ans.size();;
	printf("Case %d: %d", ++cas, ansz - 1);
	for (int i = 0; i < ansz; i++) {
	    printf(" %d", ans[i] * tmp % n);
	}
	printf("\n");
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const int N = 100005;
const double eps = 1e-8;

int t, n, a[N];
struct Seg {
    double one, zero, x;
    Seg() {}
    Seg(double one, double zero, double x) {
    this->one = one;
    this->zero = zero;
    this->x = x;
    }
} s[N];

double cal(double one, double zero) {
    return one / (one + zero);
}

double solve(int n) {
    int sn = 0;
    int one = 0, zero = 0, now = 0;
    while (now < n && !a[now]) {now++;}
    while (n >= 0 && a[n]) n--;
    if (now > n) return 0.0;
    while (now <= n) {
    double one = 0, zero = 0;
    while (a[now]) {
        one += 1;
        now += 1;
    }
    while (now <= n && !a[now]) {
        zero += 1;
        now += 1;
    }
    s[sn].one = one;
    s[sn].zero = zero;
    s[sn++].x = cal(one, zero);
    }
    stack<Seg> st;
    st.push(s[0]);
    for (int i = 1; i < sn; i++) {
    
    Seg now = s[i];

    while (!st.empty() && st.top().x - now.x > -eps) {
        Seg pre = st.top();
        st.pop();
        pre.one += now.one;
        pre.zero += now.zero;
        pre.x = cal(pre.one, pre.zero);
        now = pre;
    }
    st.push(now);

    }
    double ans = 0;
    while (!st.empty()) {
    Seg now = st.top();
    st.pop();
    ans += (1 - now.x) * (1 - now.x) * now.one + now.x * now.x * now.zero;
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("%.6lf\n", solve(n - 1));
    }
    return 0;
}

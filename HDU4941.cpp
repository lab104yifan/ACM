#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

#define MP(a,b) make_pair(a,b)

typedef pair<int, int> pii;
int t, n, m, k, xn, yn;
map<pii, int> val;
map<int, int> X;
map<int, int> Y;

void add(map<int, int> &X, int x, int &xn) {
    if (X.count(x)) return;
    X[x] = xn++;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	val.clear();
	X.clear();
	Y.clear();
	xn = yn = 0;
	scanf("%d%d%d", &n, &m, &k);
	int x, y, v;
	while (k--) {
	    scanf("%d%d%d", &x, &y, &v);
	    add(X, x, xn);
	    add(Y, y, yn);
	    val[MP(X[x],Y[y])] = v;
	}
	scanf("%d", &k);
	int q, a, b;
	printf("Case #%d:\n", ++cas);
	while (k--) {
	    scanf("%d%d%d", &q, &a, &b);
	    if (q == 1) {
		add(X, a, xn);
		add(X, b, xn);
		swap(X[a], X[b]);
	    }
	    else if (q == 2) {
		add(Y, a, yn);
		add(Y, b, yn);
		swap(Y[a], Y[b]);
	    }
	    else {
		if (val.count(MP(X[a], Y[b])))
		    printf("%d\n", val[MP(X[a],Y[b])]);
		else
		    printf("0\n");
	    }
	}
    }
    return 0;
}

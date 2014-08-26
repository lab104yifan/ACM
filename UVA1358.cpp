#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long type;

struct Frac {

    type a, b;

    Frac() {a = 0; b = 1;}
    Frac(type a, type b) {this->a = a; this->b = b; deal();}

    void init() {a = 0; b = 1;}

    type gcd(type a, type b) {
	while (b) {
	    type tmp = a % b;
	    a = b;
	    b = tmp;
	}
	return a;
    }

    void deal() {
	type d = gcd(a, b);
	a /= d; b /= d;
	if (b < 0) {
	    a = -a;
	    b = -b;
	}
    }

    Frac operator + (Frac c) {
	Frac ans;
	ans.a = a * c.b + b * c.a;
	ans.b = b * c.b;
	ans.deal();
	return ans;
    }

    Frac operator - (Frac c) {
	Frac ans;
	ans.a = a * c.b - b * c.a;
	ans.b = b * c.b;
	ans.deal();
	return ans;
    }

    Frac operator * (Frac c) {
	Frac ans;
	ans.a = a * c.a;
	ans.b = b * c.b;
	ans.deal();
	return ans;
    }

    Frac operator / (Frac c) {
	Frac ans;
	ans.a = a * c.b;
	ans.b = b * c.a;
	ans.deal();
	return ans;
    }

    void operator += (Frac c) {*this = *this + c;}
    void operator += (type c) {*this = *this + Frac(c, 1);}
    void operator -= (Frac c) {*this = *this - c;}
    void operator *= (Frac c) {*this = *this * c;}
    void operator /= (Frac c) {*this = *this / c;}

    bool operator > (Frac c) {return a * c.b > b * c.a;}
    bool operator == (Frac c) { return a * c.b == b * c.a;}
    bool operator < (Frac c) {return !(*this < c && *this == c);}
    bool operator >= (Frac c) {return !(*this < c);}
    bool operator <= (Frac c) {return !(*this > c);}
    
    bool operator != (Frac c) {return !(*this == c);}
    bool operator != (type c) {return *this != Frac(c, 1);}

    void operator = (type c) {this->a = c; this->b = 1;}
};

typedef long long ll;

Frac A[15][15];

int t, m, n, next[15];
char str[15];

void getnext() {
    next[0] = next[1] = 0;
    int j = 0;
    for (int i = 2; i <= n; i++) {
	while (j && str[i] != str[j + 1]) j = next[j];
	if (str[i] == str[j + 1]) j++;
	next[i] = j;
    }
}

void build() {
    for (int i = 0; i <= n; i++)
	for (int j = 0; j <= n + 1; j++)
	    A[i][j].init();
    getnext();
    A[n][n] = 1;
    for (int i = 0; i < n; i++) {
	A[i][i] = 1;
	A[i][n + 1] = 1;
	for (int j = 0; j < m; j++) {
	    if (str[i + 1] == j + 'A')
		A[i][i + 1] += Frac(-1, m);
	    else {
		int tmp = i;
		int flag = 1;
		while (tmp) {
		    tmp = next[tmp];
		    if (str[tmp + 1] == j + 'A') {
			flag = 0;
			A[i][tmp + 1] += Frac(-1, m);
			break;
		    }
		}
		if (flag) A[i][0] += Frac(-1, m);
	    }
	}
    }
}

ll gauss() {
    for (int i = 0; i <= n; i++) {
	int r;
	for (r = i; r <= n; r++)
	    if (A[r][i] != 0) break;
	for (int j = i; j <= n + 1; j++)
	    swap(A[i][j], A[r][j]);
	for (int j = n + 1; j > i; j--)
	    A[i][j] /= A[i][i];
	A[i][i] = 1;
	for (int j = 0; j <= n; j++) {
	    if (i == j) continue;
	    if (A[j][i] != 0) {
		for (int k = n + 1; k > i; k--)
		    A[j][k] -= A[j][i] * A[i][k];
		A[j][i] = 0;
	    }
	}
    }
    return (A[0][n + 1] / A[0][0]).a;
}

int main() {
    int cas = 0;
    scanf("%d", &t);
    while (t--) {
	scanf("%d%s", &m, str + 1);
	n = strlen(str + 1);
	build();
	printf("Case %d:\n", ++cas);
	printf("%lld\n", gauss());
	if (t) printf("\n");
    }
    return 0;
}

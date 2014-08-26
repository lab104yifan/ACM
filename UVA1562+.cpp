#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
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
    void operator -= (Frac c) {*this = *this - c;}
    void operator *= (Frac c) {*this = *this * c;}
    void operator /= (Frac c) {*this = *this / c;}

    bool operator > (Frac c) {return a * c.b > b * c.a;}
    bool operator == (Frac c) {return a * c.b == b * c.a;}
    bool operator == (type c) {return *this == Frac(c, 1);}
    bool operator < (Frac c) {return !(*this > c || *this == c);}
    bool operator < (type c) {return *this < Frac(c, 1);}
    bool operator >= (Frac c) {return !(*this < c);}
    bool operator <= (Frac c) {return !(*this > c);}
    bool operator <= (type c) {return *this <= Frac(c, 1);}
    bool operator != (Frac c) {return !(*this == c);}
    bool operator != (type c) {return *this != Frac(c, 1);}

    void operator = (type c) {this->a = c; this->b = 1;}
};

typedef long long ll;

int t, n, m, hash[1005];
char str[205];

Frac A[15][15];

void build() {
    n = 0, m = 0;
    int flag = 1;
    memset(hash, -1, sizeof(hash));
    for (int i = 0; i < 15; i++)
	for (int j = 0; j < 15; j++)
	    A[i][j].init();
    int len = strlen(str), i = 0;
    while (i <= len) {
	if (str[i] >= 'A' && str[i] <= 'Z') {
	    int idx = str[i] - 'A' + 1;
	    i++;
	    if (str[i] >= 'a' && str[i] <= 'z') {
		idx = idx * 26 + str[i] - 'a' + 1;
		i++;
	    }
	    if (hash[idx] == -1) 
		hash[idx] = n++;
	    if (str[i] >= '0' && str[i] <= '9') {
		A[hash[idx]][m] += Frac(flag * (str[i] - '0'), 1);
		i++;
	    }
	    else {
		A[hash[idx]][m] += Frac(flag, 1);
	    }
	}
	if (str[i] == '=') flag = -1;
	if (str[i] == '+' || str[i] == '=' || str[i] == '\0') {
	    i++; m++;
	}
    }
}

ll gcd(ll a, ll b) {
    while (b) {
	ll tmp = a % b;
	a = b;
	b = tmp;
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

bool gauss() {
    int i = 0, j = 0;
    while (i < n && j < m) {
	int r;
	for (r = i; r < n; r++)
	    if (A[r][j] != 0) break;
	if (r == n) {
	    j++;
	    continue;
	}
	for (int k = j; k <= m; k++) swap(A[i][k], A[r][k]);
	for (int k = j + 1; k <= m; k++)
	    A[i][k] /= A[i][j];
	A[i][j] = 1;
	for (int k = 0; k < n; k++) {
	    if (i == k) continue;
	    if (A[k][j] != 0) {
		for (int x = j + 1; x <= m; x++)
		    A[k][x] -= A[k][j] * A[i][x];
		A[k][j] = 0;
	    }
	}
	i++;
    }
    for (int k = i; k < n; k++)
	if (A[k][m] != 0) return false;
    for (int k = m - 1; k >= 0; k--) {
	if (A[k][k] == 0) {
	    A[k][k] = 1;
	    A[k][m] = 1;
	    for (int j = k - 1; j >= 0; j--) {
		A[j][m] -= A[j][k];
		A[j][k] = 0;
	    }
	}
    }
    Frac out[15];
    ll d = 1, put[15];
    for (int k = 0; k < m; k++) {
	out[k] = A[k][m] / A[k][k];
	d = lcm(d, out[k].b);
    }
    for (int k = 0; k < m; k++)
	put[k] = out[k].a * (d / out[k].b);
    int flag = 1;
    for (int k = 0; k < m; k++)
	if (put[k] > 0) {
	    flag = 0;
	    break;
	}
    if (flag) {
	for (int k = 0; k < m; k++)
	    put[k] = -put[k];
    }
    for (int k = 0; k < m; k++)
	if (put[k] < 0) return false;
    for (int k = 0; k < m; k++) 
	printf("%lld%c", put[k], k == m - 1 ? '\n' : ' ');
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
	scanf("%s", str);
	build();
	if (!gauss()) printf("IMPOSSIBLE\n");
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 105;

int n = 0, len, now, c;
long long value;
char str[1000005];

long long gcd(long long a, long long b) {
    if (!b) return a;
    return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

struct GaussNum {
    long long a, b, mu;
    GaussNum() {mu = 1;}
    GaussNum(long long a, long long b) {
	this->a = a; this->b = b; this->mu = 1;
    }
    void deal() {
	long long d = gcd(gcd(a, mu), gcd(b, mu));
	//while (!mu);
	this->a /= d;
	this->b /= d;
	this->mu /= d;
    }
    GaussNum operator + (GaussNum c) {
	GaussNum ans;
	ans.mu = lcm(mu, c.mu);
	ans.a = ans.mu / mu * a + ans.mu / c.mu * c.a;
	ans.b = ans.mu / mu * b + ans.mu / c.mu * c.b;
	ans.deal();
	return ans;
    }
    GaussNum operator - (GaussNum c) {
	GaussNum ans;
	ans.mu = lcm(mu, c.mu);
	ans.a = ans.mu / mu * a - ans.mu / c.mu * c.a;
	ans.b = ans.mu / mu * b - ans.mu / c.mu * c.b;
	ans.deal();
	return ans;
    }
    GaussNum operator * (GaussNum c) {
	GaussNum ans;
	ans.a = a * c.a - b * c.b;
	ans.b = a * c.b + b * c.a;
	ans.mu = mu * c.mu;
	ans.deal();
	return ans;
    }
    GaussNum operator / (GaussNum c) {
	GaussNum ans;
	long long d = lcm(mu, c.mu);
	
	while (d % c.mu);
	GaussNum x, y;
	while (!d);
	x.a = d / mu * a;
       	x.b = d / mu * b;
	while (!c.mu);
	while ((!d) && (!(d / c.mu)));
	while (!c.a && !c.b);
	y.a = d / c.mu * c.a;
       	y.b = d / c.mu * c.b;
	ans.a = (x.a * y.a + x.b * y.b);
	ans.b = (x.b * y.a - x.a * y.b);
	ans.mu = (y.a * y.a + y.b * y.b);
	//if (!y.a && !y.b) while(1);
	ans.deal();
	return ans;
    }
};

GaussNum a[N][N];
double ans[N][2];

int gettoken() {
    while (str[now] != '(' && str[now] != ',' && str[now] != ')' && !((str[now] >= '0' && str[now] <= '9') || str[now] == '-')) now++;
    if (now == len) return -1;
    if (str[now] == '(') {
	now++;
	return 1;
    }
    else if (str[now] == ',') {
	now++;
	return 2;
    }
    else if (str[now] == ')') {
	now++;
	return 3;
    }
    else if ((str[now] >= '0' && str[now] <= '9') || str[now] == '-') {
	value = 0;
	long long flag = 1;
	if (str[now] == '-') {
	    flag = -1;
	    now++;
	}
	while (str[now] != ',' && str[now] != ')') {
	    if (str[now] >= '0' && str[now] <= '9') {
		value = value * 10 + (str[now] - '0');
	    }
	    else {while(1);}
	    now++;
	}
	value *= flag;
	return 4;
    }
    return 5;
}

void getNum() {
    if (now == len) return;
    if (gettoken() == 1) {
	if (gettoken() == 4) {
	    a[n][c].a = value;
	}else {while(1);}
	if (gettoken() == 2) {
	    if (gettoken() == 4) {
		a[n][c].b = value;
		a[n][c++].mu = 1;
	    } else {while(1);}
	    if (gettoken() == 3) {
		getNum();
	    }else {while(1);}
	}
	else {while(1);}
    }else {while(1);}
}

void build() {
    now = 0;
    c = 0;
    len = strlen(str);
    getNum();
    /*for (int i = 0; i < n; i++) {
	for (int j = 0; j <= n; j++) {
	    printf("(%.1lf, %.1lf) ", a[i][j].a, a[i][j].b);
	}
	printf("\n");
    }*/
}

bool gauss() {
    for (int i = 0; i < n; i++) {
	int k = i;
	for (; k < n; k++)
	    if (a[k][i].a || a[k][i].b) break;
	if (k == n) return false;
	for (int j = 0; j <= n; j++)
	    swap(a[k][j], a[i][j]);
	for (int j = 0; j < n; j++) {
	    if (i == j) continue;
	    if (a[j][i].a || a[j][i].b) {
		for (int k = n; k >= i; k--)
		    a[j][k] = (a[j][k] - (a[j][i] * a[i][k] / a[i][i]));
	    }
	}
    }
    for (int i = n - 1; i >= 0; i--) {
	GaussNum tmp = a[i][n] / a[i][i];
	while (!tmp.mu);
	ans[i][0] = tmp.a * 1.0 / tmp.mu;
	ans[i][1] = tmp.b * 1.0 / tmp.mu;
    }
    return true;
}

int main() {
    int bo = 0;
    while (gets(str) != NULL) {
	if (str[0] == '\0') {
	    while (n != c - 1);
	    if (bo++) printf("\n");
	    if (gauss()) {
		for (int i = 0; i < n; i++)
		    printf("(%.1lf,%.1lf)\n", ans[i][0], ans[i][1]);
	    }
	    else printf("No solution\n");
	    n = 0;
	}
	else {
	    build();
	    n++;
	}
    }
    while (n);
    return 0;
}

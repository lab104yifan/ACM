#include <cstdio>
#include <cstring>
#include <cmath>
#include <stack>
using namespace std;

const double pi = acos(-1.0);
const int N = 1005;
double B, H;
char T[N], R[N];

void init() {
    int len;
    scanf("%s%s", R, T);
    len = strlen(T);
    T[len++] = '#';
    len = strlen(R);
    R[len++] = '#';
}

int getpri(char c, int bo) {
    if (c == '+' || c == '-') return 2 + bo;
    if (c == '*' || c == '/') return 4 + bo;
    if (c == '(' && bo) return 6;
    if ((c == ')' && bo) || (c == '(' && bo == 0)) return 1;
    if (c == '#') return 0;
}

double gao(double a, double b, char c) {
    if (c == '+') return a + b;
    if (c == '-') return a - b;
    if (c == '*') return a * b;
    if (c == '/') return a / b;
}

double cal(char *expr, double x) {
    int len = strlen(expr);
    stack<double> val;
    stack<char> op;
    op.push('#');
    int i = 0;
    while (i < len) {
	double num = 0;
	if (expr[i] >= '0' && expr[i] <= '9') {
	    while (expr[i] >= '0' && expr[i] <= '9') {
		num = num * 10 + expr[i] - '0';
		i++;
	    }
	    if (expr[i] == '.') {
		double k = 1;
		i++;
		while (expr[i] >= '0' && expr[i] <= '9') {
		    k /= 10;
		    num += k * (expr[i] - '0');
		    i++;
		}
	    }
	    val.push(num);
	}
	else if (expr[i] == 'x') {
	    num = x;
	    i++;
	    val.push(num);
	}
	else {
	    int out = getpri(expr[i], 1);
	    int in = getpri(op.top(), 0);
	    if (out == in)
		op.pop();
	    else if (out < in) {
		while (getpri(op.top(), 0) > out) {
		    double b = val.top();
		    val.pop();
		    double a = val.top();
		    val.pop();
		    double res = gao(a, b, op.top());
		    val.push(res);
		    op.pop();
		}
		if (getpri(op.top(), 0) == out)
		    op.pop();
		else op.push(expr[i]);
	    }
	    else
		op.push(expr[i]);
	    i++;
	}
    }
    return val.top();
}

double S(double up, double down, double h) {
    return (up + down) * h / 2;
}

double S2(double down, double up, double h) {
    double r1 = down / 2;
    double r2 = up / 2;
    return 1.0 / 3 * h * pi * (r1 * r1 + r2 * r2 + r1 * r2);
}

void solve() {
    double bdown = cal(R, 0) * 2;
    double bup = cal(R, H) * 2;
    double sdown = (cal(R, B) - cal(T, B)) * 2;
    double sup = (cal(R, H) - cal(T, H)) * 2;
    double sw = (S2(bdown, bup, H) - S2(sdown, sup, H - B));
    double l = B, r = H;
    double s;
    for (int i = 0; i < 100; i++) {
	double mid = (l + r) / 2;
	double tmpup = ((mid - B) * sup + (H - mid) * sdown) / (H - B);
	s = S(tmpup, sdown, mid - B);
	if (s > sw) r = mid;
	else l = mid;
    }
    printf("Pour %lf litres / %lf cm of water.\n", s, l - B);
}

int main() {
    while (~scanf("%lf%lf", &H, &B) && B || H) {
	init();
	solve();
    }
    return 0;
}

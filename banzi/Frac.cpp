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

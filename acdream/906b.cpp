#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

string str;

int main() {
	while (cin >> str) {
		string a, b, c;
		a = "000000000000000000000000032767";
		b = "000000000000000000002147483647";
		c = "000000000009223372036854775807";
		int s = 0;
		int n = str.length();
		if (str[0] == '-') {
			n--;
			s++;
			a = "000000000000000000000000032768";
			b = "000000000000000000002147483648";
			c = "000000000009223372036854775808";
		}
		string tmp = "";
		for (int i = 30 - n; i > 0; i--)
			tmp += '0';
		for (int i = s; i < n + s; i++)
			tmp += str[i];
		str = tmp;
		if (str <= a) printf("short\n");
		else if (str <= b) printf("int\n");
		else if (str <= c) printf("long long\n");
		else printf("It is too big!\n");
	}
	return 0;
}

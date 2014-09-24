#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

int t;
string str;

void handle() {
	string tmp = "";
	for (int i = 0; i < str.length(); i++)
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
			tmp += str[i];
		}
	str = tmp;
}

int n;
bool solve1() {
	for (int i = 0; i < n; i++) {
		string A = "";
		for (int j = 0; j <= i; j++)
			A += str[j];
		int bl = n - (i + 1) * 3;
		if (bl <= 0 || bl % 2) continue;
		string B = "";
		for (int j = i + 1; j < i + 1 + bl / 2; j++)
			B += str[j];
		if (A != B && A + B + A + B + A == str) return true;
	}
	return false;
}

bool judge(string AB, string C) {
	for (int i = 0; i < AB.length(); i++) {
		string A = "", B = "";
		for (int j = 0; j <= i; j++)
			A += AB[j];
		for (int j = i + 1; j < AB.length(); j++)
			B += AB[j];
		if (A == "" || B == "" || C == "") continue;
		if (A == B || A == C || C == B) continue;
		return true;
	}
	return false;
}

bool solve2() {
	for (int i = 0; i < n; i++) {
		string AB = "";
		for (int j = 0; j <= i; j++)
			AB += str[j];
		int cl = n - (i + 1) * 3;
		if (cl <= 0) continue;
		string C = "";
		for (int j = 2 * i + 2; j < 2 * i + 2 + cl; j++)
			C += str[j];
		if (judge(AB, C) && AB + AB + C + AB == str) return true;
	}
	return false;
}

int main() {
	scanf("%d%*c", &t);
	while (t--) {
		getline(cin, str);
		handle();
		n = str.length();
		if (solve1() || solve2()) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

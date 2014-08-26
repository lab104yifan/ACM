#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<string> g;
string s, a, b;

void solve() {
    cout << s << " " << a << " " << b << endl;
    for (int i = 0; i < g.size(); i++) {
	string mid = "";
	int l = 0, r = a.length() - 1;
	int ll, rr;
	for (ll = 0; ll < g[i].length(); ll++) {
	    if (g[i][ll] == a[l]) l++;
	    else break;
	}
	for (rr = g[i].length() - 1; rr >= 0; rr--) {
	    if (g[i][rr] == a[r]) r--;
	    else break;
	}
	if (a[l] != '*' || a[r] != '*' || ll - rr > 1) continue;
	cout << "mv " << g[i] << " ";
	int j;
	for (j = 0; j < b.length(); j++) {
	    if (b[j] == '*') break;
	    cout << b[j];
	}
	for (; ll <= rr; ll++)
	    cout << g[i][ll];
	j++;
	for (; j < b.length(); j++)
	    cout << b[j];
	cout << endl;
    }
}

int main() {
    while (cin >> s) {
	g.clear();
	if (s != "end") {
	    g.push_back(s);
	    while (cin >> s) {
		if (s == "end") break;
		g.push_back(s);
	    }
	}
	while (cin >> s) {
	    if (s == "end") break;
	    cin >> a >> b;
	    solve();
	}
	printf("\n");
    }
    return 0;
}

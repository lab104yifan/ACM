#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int N = 100005;

string s, name;
vector<string> g;
vector<string> ans;
int next[N], ll, rr;
bool have;

void getnext(string name) {
    next[0] = next[1] = 0;
    int j = 0;
    for (int i = 2; i <= name.length(); i++) {
	while (j && name[i - 1] != name[j]) j = next[j];
	if (name[i - 1] == name[j]) j++;
	next[i] = j;
    }
}

bool find(string name) {
    int u = ll, j = 0;
    if (u == rr) return true;
    for (int i = 0; i < name.length(); i++) {
	while (j && name[i] != g[u][j]) j = next[j];
	if (name[i] == g[u][j]) j++;
	if (j == g[u].length()) {
	    u++;
	    j = 0;
	    if (u == rr) return true;
	}
    }
    return false;
}

bool check() {
    if (!have) return name == g[0];
    int l = 0, r = name.length() - 1;
    if (s[s.length() - 1] != '*') {
	string last = g[g.size() - 1];
	for (int i = last.length() - 1; i >= 0; i--) {
	    if (name[r] != last[i]) return false;
	    r--;
	}
    }
    if (s[0] != '*') {
	string fir = g[0];
	for (int i = 0; i < fir.length(); i++) {
	    if (name[l] != fir[i]) return false;
	    l++;
	}
    }
    string tmp = "";
    for (int i = l; i <= r; i++)
	tmp += name[i];
    getnext(tmp);
    if (find(tmp)) return true;
    return false;
}

void init() {
    g.clear();
    string tmp = "";
    have = false;
    for (int i = 0; i < s.length(); i++) {
	if (s[i] == '*') {
	    have = true;
	    if (tmp != "") 
		g.push_back(tmp);
	    tmp = "";
	    continue;
	}
	tmp += s[i];
    }
    if (tmp != "")
	g.push_back(tmp);
    ll = 0;
    rr = g.size();
    if (s[0] != '*') ll++;
    if (s[s.length() - 1] != '*') rr--;
}

int main() {
    int flag = 0;
    int bo = 0;
    while (getline(cin, s)) {
	init();
	flag = 0;
	ans.clear();
	while (getline(cin, name)) {
	    if (name == "") break;
	    if (check()) {
		flag = 1;
		ans.push_back(name);
	    }
	}
	if (flag) {
	    if (bo) printf("\n");
	    else bo = 1;
	    cout << "MATCHES FOR THE PATTERN: " << s << endl;
	    for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << endl;
	}
    }
    return 0;
}

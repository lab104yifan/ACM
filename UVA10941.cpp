#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

int t;
set<string> s, vis;
string x, y;

void init() {
	cin >> x >> y;
	string tmp;
	int q;
	cin >> q;
	s.clear();
	while (q--) {
		cin >> tmp;
		s.insert(tmp);
	}
}

struct State {
	string str;
	int val;
	State() {}
	State (string str, int val) {
		this->str = str;
		this->val = val;
	}
};

int solve() {
	queue<State> Q;
	if (x.length() > y.length())
		Q.push(State(x.substr(y.length()), 0));
	else Q.push(State(y.substr(x.length()), 0));
	vis.clear();
	vis.insert(Q.front().str);
	while (!Q.empty()) {
		State u = Q.front();
		Q.pop();
		if (u.str == "")
			return u.val;
		set<string>::iterator now = s.lower_bound(u.str);
		for (set<string>::iterator it = now;
				it != s.end() && it->substr(0, u.str.length()) == u.str; it++) {
			string tmp = it->substr(u.str.length());
			if (vis.find(tmp) == vis.end()) {
				vis.insert(tmp);
				Q.push(State(tmp, u.val + 1));
			}
		}
		for (int i = u.str.length(); i > 0; i--) {
			set<string>::iterator it = s.find(u.str.substr(0, i));
			if (it != s.end()) {
				string tmp = u.str.substr(it->length());
				if (vis.find(tmp) == vis.end()) {
					vis.insert(tmp);
					Q.push(State(tmp, u.val + 1));
				}
			}
		}
	}
	return -1;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		init();
		cout << solve() << endl;
	}
	return 0;
}

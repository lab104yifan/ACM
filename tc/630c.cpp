#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

typedef pair<string, int> pii;

class SuffixArrayDiv2 {
    public:
    string smallerOne(string s) {
	int n = s.length();
	pii save[55];
	for (int i = n - 1; i >= 0; i--) {
	    string tmp = "";
	    for (int j = i; j < n; j++)
		tmp += s[j];
	    save[i].first = tmp;
	    save[i].second = i;
	}
	sort(save, save + n);
	for (int t = 0; t < n; t++) {
	    if (s[t] == 'a') continue;
	    string ss = s;
	    ss[t]--;
	    pii sav[55];
	    for (int i = n - 1; i >= 0; i--) {
		string tmp = "";
		for (int j = i; j < n; j++)
		    tmp += ss[j];
		sav[i].first = tmp;
		sav[i].second = i;
	    }
	    sort(sav, sav + n);
	    int k = 0;
	    for (; k < n; k++)
		if (save[k].second != sav[k].second) break;
	    if (k == n) return "Exists";
	}
	return "Does not exist";
    }
};

string sb;
SuffixArrayDiv2 gao;

int main() {
    while (cin >> sb) {
	cout << gao.smallerOne(sb) << endl;
    }
    return 0;
}

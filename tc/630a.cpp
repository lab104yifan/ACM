#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;

class DoubleLetter {
    public:
	string ableToSolve(string S) {
	    while (1) {
		int n = S.length();
		string tmp = "";
		int flag = 1;
		for (int i = 0; i < n - 1; i++) {
		    if (S[i] == S[i + 1]) {
			flag = 0;
			for (int j = 0; j < n; j++) {
			    if (j == i || j == i + 1) continue;
			    tmp += S[j];
			}
			break;
		    }
		}
		if (flag) break;
		S = tmp;
	    }
	    if (S == "") return "Possible";
	    else return "Impossible";
	}
};

int main() {
    DoubleLetter gao;
    string sb;
    while (cin >> sb) {
	cout << gao.ableToSolve(sb) << endl;
    }
    return 0;
}

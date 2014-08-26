#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

class Egalitarianism3Easy {
public:
    int bitcount(int x) {
	int ans = 0;
	while (x) {
	    ans += (x&1);
	    x >>= 1;
	}
	return ans;
    }

    int maxCities(int n, vector<int> a, vector<int> b, vector<int> len) {
	int g[15][15];
	for (int i = 1; i <= 10; i++)
	    for (int j = 1; j <= 10; j++) {
		if (i == j) g[i][j] = 0;
		else g[i][j] = 1000000000;
	    }
	for (int i = 0; i < n - 1; i++)
	    g[a[i]][b[i]] = g[b[i]][a[i]] = len[i];
	for (int k = 1; k <= n; k++) {
	    for (int i = 1 ; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
		    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		}
	    }
	}
	int tmp[15], tn;
	int ans = 1;
	for (int i = 1; i < (1<<n); i++) {
	    tn = 0;
	    for (int j = 0; j < n; j++) {
		if (i&(1<<j)) {
		    tmp[tn++] = j + 1;
		}
	    }
	    int ss = -1;
	    int flag = 0;
	    for (int j = 0; j < tn; j++) {
		for (int k = j + 1; k < tn; k++) {
		    if (ss == -1) ss = g[tmp[j]][tmp[k]];
		    else {
			if (ss != g[tmp[j]][tmp[k]]) {
			    flag = 1;
			    break;
			}
		    }
		}
		if (flag)
		    break;
	    }
	    if (flag == 0) ans = max(ans, bitcount(i));
	}
	return ans;
    }
};

int n;
vector<int> a, b, c;
 Egalitarianism3Eay gao;

int main() {
    while (cin >> n) {
	a.clear();
	b.clear();
	c.clear();
	int num;
	for (int i = 0; i < n - 1; i++) {
	    cin >> num;
	    a.push_back(num);
	}
	for (int i = 0; i < n - 1; i++) {
	    cin >> num;
	    b.push_back(num);
	}
	for (int i = 0; i < n - 1; i++) {
	    cin >> num;
	    c.push_back(num);
	}
	cout << gao.maxCities(n, a, b, c) << endl;
    }
    return 0;
}

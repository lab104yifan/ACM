#include <cstdio>
#include <cstring>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int cal(string tmp) {
	int ans = 0;
	int n = tmp.length();
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int l = i, r = j;
			int flag = 1;
			while (l < r) {
				if (tmp[l] != tmp[r]) {
					flag = 0;
					break;
				}
				l++; r--;
			}
			if (flag) {
				ans = max(ans, j - i + 1);
			}
		}
	}
	return ans;
}

int main() {
	int t;
	int n, m;
	scanf("%d", &t);

	while (t--) {
		int Min = 100000;
		string ans = "zzzzzzzzzzzzzzzzzzzzzzzz";
		scanf("%d%d", &m, &n);
		for (int i = 0; i < (1<<n); i++) {
			string tmp = "";
			for (int j = 0; j < n; j++) {
				if (i&(1<<j))
					tmp += 'a';
				else
					tmp += 'b';
			}
			int save = cal(tmp);
			if (save < Min) {
				Min = save;
				ans = tmp;
			} else if (save == Min) {
				if (tmp < ans)
					ans = tmp;
			}
		}
		cout << ans << endl;
	}
	return 0;
}

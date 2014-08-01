#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;

const int N = 1005;

int n, q[N][2];

bool is_stack() {
    stack<int> S;
    for (int i = 0; i < n; i++) {
	if (q[i][0] == 1) {
	    S.push(q[i][1]);
	}
	else {
	    if (S.empty() || S.top() != q[i][1]) return false;
	    S.pop();
	}
    }
    return true;
}

bool is_queue() {
    queue<int> Q;
    for (int i = 0; i < n; i++) {
	if (q[i][0] == 1) {
	    Q.push(q[i][1]);
	}
	else {
	    if (Q.empty() || Q.front() != q[i][1]) return false;
	    Q.pop();
	}
    }
    return true;
}

bool is_priqueue() {
    priority_queue <int> Q;
    for (int i = 0; i < n; i++) {
	if (q[i][0] == 1) {
	    Q.push(q[i][1]);
	}
	else {
	    if (Q.empty() || Q.top() != q[i][1]) return false;
	    Q.pop();
	}
    }
    return true;
}

void solve() {
    int cnt = 0, ans;
    if (is_stack()) ans = 0, cnt++;
    if (is_queue()) ans = 1, cnt++;
    if (is_priqueue()) ans = 2, cnt++;
    if (cnt == 0) printf("impossible\n");
    else if (cnt > 1) printf("not sure\n");
    else {
	if (ans == 0) printf("stack\n");
	else if (ans == 1) printf("queue\n");
	else printf("priority queue\n");
    }
}

int main() {
    while (~scanf("%d", &n)) {
	for (int i = 0; i < n; i++)
	    scanf("%d%d", &q[i][0], &q[i][1]);
	solve();
    }
    return 0;
}

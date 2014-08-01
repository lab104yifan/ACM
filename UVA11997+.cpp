#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 755;

int n, a[N][N];
struct State {
    int b, sum;
    State() {}
    State(int b, int sum) {
	this->b = b;
	this->sum = sum;
    }
    bool operator < (const State& c) const {
	return sum > c.sum;
    }
};

void merge(int *a, int * b) {
    priority_queue<State> Q;
    for (int i = 0; i < n; i++)
	Q.push(State(0, a[i] + b[0]));
    for (int i = 0; i < n; i++) {
	State now = Q.top();
	a[i] = now.sum;
	Q.pop();
	Q.push(State(now.b + 1, now.sum - b[now.b] + b[now.b + 1]));
    }
}

int main() {
    while (~scanf("%d", &n)) {
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < n; j++)
		scanf("%d", &a[i][j]);
	    sort(a[i], a[i] + n);
	}
	for (int i = 1; i < n; i++)
	    merge(a[0], a[i]);
	for (int i = 0; i < n - 1; i++)
	    printf("%d ", a[0][i]);
	printf("%d\n", a[0][n - 1]);
    }
    return 0;
}

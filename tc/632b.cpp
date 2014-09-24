#include <vector>
#include <cstdio>
using namespace std;

typedef long long ll;

const int N = 2005;
const ll MOD = 1000000007;

class CandyCupRunningCompetition {

public:
	int parent[N];
	ll pow3[N];

	void init() {
		pow3[0] = 1;
		parent[0] = 0;
		for (int i = 1; i < N; i++) {
			parent[i] = i;
			pow3[i] = pow3[i - 1] * 3 % MOD;
		}
	}

	int find(int x) {
		return parent[x] == x ? x : parent[x] = find(parent[x]);
	}
	
	int find2(int x) {
		return parent[x] == x ? x : find(parent[x]);
	}
	int findMaximum(int N, vector <int> A, vector <int> B) {
		init();
		int n = A.size();
		ll ans = 0;
		for (int i = n - 1; i >= 0; i--) {
			int pa = find(A[i]);
			int pb = find(B[i]);
			if (pa == pb) continue;
			int tmp = parent[pa];
			parent[pa] = pb;
			if (find2(0) == find2(N - 1)) {
				ans = (ans + pow3[i]) % MOD;
				parent[pa] = tmp;
			}
		}
		return (int)ans;
	}
};

CandyCupRunningCompetition gao;
vector<int> A, B;
int n;

int main() {
	while (~scanf("%d", &n)) {
		A.clear(); B.clear();
		int tmp;
		for (int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			A.push_back(tmp);
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			B.push_back(tmp);
		}
		scanf("%d", &n);
		printf("%d\n", gao.findMaximum(n, A, B));
	}
	return 0;
}

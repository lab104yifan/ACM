#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
#define MP(a,b) make_pair(a,b)
const int INF = 0x3f3f3f3f;

class CatsOnTheLineDiv1 {
	vector<pii> g;
	public:
		int getNumber(vector<int> position, vector<int> count, int time) {
			int n = position.size();
			for (int i = 0; i < n; i++)
				g.push_back(MP(position[i] - time, count[i]));
			sort(g.begin(), g.end());
			int le = -INF, sink = -INF, ans = 0;
			for (int i = 0; i < n; i++) {
				int l = g[i].first;
				int r = v + 2 * time;
				if (l <= sink) continue;
				le = max(le, l);
				if (r - l + 1 < count[i]) {
					ans++;
					sink = r;
				} else {
					le += count[i];
				}
			}
			return ans;
		}
};

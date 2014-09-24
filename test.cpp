#include <cstdio>
#include <cmath>

using namespace std;

double n;

int main() {
	while (~scanf("%lf", &n)) {
		double sb = 0;
		sb += log10(n) * n;
		int tmp = (int)pow(10, sb - floor(sb));
		printf("%d\n", tmp);
	}
	return 0;
}

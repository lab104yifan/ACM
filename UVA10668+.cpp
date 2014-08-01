/*
ID      :
NAME    :
CODER   : Arman Kamal
TYPE    :
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <deque>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

# define FOR(i, a, b) for (int i=a; i<b; i++)
# define REP(i, a) FOR(i,0,a)

#define EPS 1e-10
#define inf ( 1LL << 30 )
#define LL long long

#define abs(x) (((x)< 0) ? (-(x)) : (x))
#define all(x) (x).begin(), (x).end()
#define ms(x, a) memset((x), (a), sizeof(x))

# define VI vector<int>
# define VS vector<string>
# define VC vector<char>
# define pii pair<int,int>

#define mp make_pair
#define pb push_back
#define CI(x) scanf(" %d", &x)
#define CL(x) scanf(" %lld", &x)
#define READ(x) freopen(x,"r",stdin)
#define WRITE(x) freopen(x, "w",stdout)

using namespace std;

#define PI 2*acos(0.0)

double L , C , n ;
double Lp ;

int main() {
    while(scanf(" %lf %lf %lf", &L , &C , &n) == 3){
        if(L < 0 and n < 0 and C < 0)break ;
        Lp = L*(1.0  + n*C) ;
        double lo = 0 , hi = PI / 2, mid = 0 , r;
        int cnt = 0 ;
        while(lo <= hi and cnt < 50){
            mid = (lo + hi)/2.0 ;
            r = L/2.0 / sin(mid) ;
            if(r*2.0*mid < Lp) {
                lo = mid ;
            }else{
                hi = mid ;
            }
            cnt++ ;
        }


        printf("%.3lf\n", r - r*cos(mid)) ;
    }
    return 0 ;
}

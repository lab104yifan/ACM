#include<cstdio>
#include <cstring>
#include<cmath>
#include<algorithm>
#include <map>
using namespace std;
const int N = 505;

struct point
{
    int x,y,val,id;
}list[N], save[N], p[N];

int stack[N],top, vi[N];

int cross(point p0,point p1,point p2) //计算叉积  p0p1 X p0p2 
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}    

bool cmp(point p1,point p2) //极角排序函数 ， 角度相同则距离小的在前面 
{
    /*int tmp=cross(list[0],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0&&dis(list[0],p1)<dis(list[0],p2)) return true;
    else return false;*/
    if (p1.y == p2.y) return p1.x < p2.x;
    return p1.y < p2.y;
}

void init(int n) //输入，并把  最左下方的点放在 list[0]  。并且进行极角排序 
{
    int i,k;
    point p0;
    list[0] = p[0];
    p0.x=list[0].x;
    p0.y=list[0].y;
    p0.id = list[0].id;
    k=0;
    for(i=1;i<n;i++)
    {
	list[i] = p[i];
	if( (p0.y>list[i].y) || ((p0.y==list[i].y)&&(p0.x>list[i].x)) )
	{
	    p0.x=list[i].x;
	    p0.y=list[i].y;
	    p0.id = list[i].id;
	    k=i;
	}    
    }    
    list[k]=list[0];
    list[0]=p0;

    sort(list+1,list+n,cmp);
}     

void graham(int n)
{
    int i;
    if(n==1) {top=0;stack[0]=0;}
    if(n==2)
    {
	top=1;
	stack[0]=0;
	stack[1]=1;
    }    
    if(n>2)
    {
	for(i=0;i<=1;i++) stack[i]=i;
	top=1;
	for(i=2;i<n;i++)
	{
	    while(top>0&&cross(list[stack[top-1]],list[stack[top]],list[i])<0) top--;
	    top++;
	    stack[top]=i;
	}
	/*
	memset(vi, 0, sizeof(vi));
	for (int i = 0; i <= top; i++)
	    vi[stack[i]] = 1;
	int tmp = top;
	for (int i = n - 1; i >= 0; i--) {
	    if (!vi[i] && cross(list[stack[0]], list[stack[top]], list[i]) == 0)
		stack[++tmp] = i;
	}
	top = tmp;*/
	int len = top;
	stack[++top] = n - 2;
	for (int i = n - 3; i >= 0; i--) {
	    while (top > len && cross(list[stack[top - 1]], list[stack[top]], list[i]) < 0) top--;
	    top++;
	    stack[top] = i;
	}
    }    
}

int n, pn, vis[N];
map<pair<int, int>, int> sb;
void solve() {/*
    for (int i = 0; i <= top; i++)
	printf("%d ", stack[i]);
    printf("\n");*/
    for (int i = 0; i <= top; i++)
	vis[list[stack[i]].id] = 1;
    for (int i = 0; i < pn; i++) {
	if (sb[make_pair(p[i].x, p[i].y)] > 1)
	    vis[p[i].id] = 0;
    }
}

int main() {
    int cas = 0;
    while (~scanf("%d", &n) && n) {
	printf("Case #%d: ", ++cas);
	sb.clear();
	memset(vis, 0, sizeof(vis));
	int Max = 0;
	for (int i = 0; i < n; i++) {
	    scanf("%d%d%d", &save[i].x, &save[i].y, &save[i].val);
	    save[i].id = i;
	    Max = max(Max, save[i].val);
	}
	if (Max == 0) {
	    for (int i = 0; i < n; i++)
		printf("0");
	    printf("\n");
	    continue;
	}
	pn = 0;
	for (int i = 0; i < n; i++) {
	    if (save[i].val == Max) {
		if (!sb.count(make_pair(save[i].x, save[i].y))) {
		    sb[make_pair(save[i].x, save[i].y)] = 1;
		    p[pn++] = save[i];
		    continue;
		}
		else sb[make_pair(save[i].x, save[i].y)]++;
	    }
	}
	if (pn) {
	    init(pn);
	    graham(pn);
	    solve();
	}
	for (int i = 0; i < n; i++)
	    printf("%d", vis[i]);
	printf("\n");
    }
    return 0;
}

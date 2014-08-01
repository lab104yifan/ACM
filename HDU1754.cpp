#include<iostream>
#include<cstring>
#include <cstdio>
#include <cstring>
#define N 200001
using namespace std;
int num[N],p[N];
int n;
int lowbit(int t)
{
	return t&(-t);
}
void change()//找最大值初始化
{
    int i,j;
    for(i = 1;i <= n;i ++)
    {
        p[i] = num[i];
        for(j = 1;j < lowbit(i);j <<= 1)
		//找比i小的数但又在lowbit(i)+1到i这个区间上的数更新p数组
        {
			p[i]=max(p[i],p[i-j]);//j是以2倍的速度增长
        }
     }
}
void insert(int t,int sore)
{
    num[t] = sore;
    while(t <= n)
    {
        if(sore > p[t])
        p[t] = sore;
        else
        break;
        t += lowbit(t);
    }
}
int getmax(int l,int r)//找最大值
{
    int ans = num[r];
    for(;;)
    {
        ans=max(ans,num[r]);//跟r位置上的数字比较
        if(l == r) break;
        for(r = r-1;r-l >=lowbit(r);r -= lowbit(r))
        {
            if(ans < p[r])
            ans = p[r];
        }
    }//r自减1，判断r-lowbit(r)和l之间的关系如果l在区间内就不能减了而是继续循环
    return ans;//如果l比r-lowbit(r)小的话，就可以之间判断ans和p[r]的最值了。
}
int main()
{
    int m,i,id,sd,max;
    char str[2];
    while(~scanf("%d%d",&n,&m)!=EOF)
    {
       	memset(p,0,sizeof(p));
       	for(i = 1;i <= n;i ++)
		scanf("%d",&num[i]);
		//scanf("%d%*c",&num[i]);
		//若此处是这个%*c是为了消除后面的回车字符，后面就可以改为输入一个字符 
        change();
        for(i = 1;i <= m;i ++)
        {
            scanf("%s%d%d%*c",str,&id,&sd);
            if(str[0] == 'Q')
            {
                max = getmax(id,sd);
                printf("%d\n",max);
            }
            else if(str[0] == 'U')
            {
                insert(id,sd);
            }
        }
	}
	return 0;
}


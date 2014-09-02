#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#define LL long long
using namespace std;

const int MAXN=55;
const LL INF =1e12+1;

struct Edge{
    int v,next;
    Edge(){}
    Edge(int _v,int _next):v(_v),next(_next){}
}edge[MAXN*MAXN];

struct N{
    int l,r;
}a[MAXN*MAXN];

int cmp(N a,N b)
{
    if(a.l==b.l)
        return a.r>b.r;
    return a.l<b.l;
}

int head[MAXN],tol;
int vis[MAXN];
LL d[MAXN];
queue<int>q;

void init()
{
    tol=0;
    memset(head,-1,sizeof(head));
}

void add(int u,int v)
{
    edge[tol]=Edge(v,head[u]);
    head[u]=tol++;
}

void dijkstra(int st,int c)
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<52;i++)
        if(i==st)d[i]=c;
        else d[i]=INF;
    for(int i=0;i<52;i++)
    {
        if(head[i]==-1)
            continue;

        int x;
        LL m=INF;
        for(int j=0;j<52;j++)
        {
            if(!vis[j]&&d[j]<m){
                x=j;
                m=d[x];
            }
        }
        vis[x]=1;
        LL t=0,p=d[x];
        if(x<26)
            while((p+t)-(p+t)/20-((p+t)%20==0?0:1)<d[x])
            {
                t+=d[x]-((p+t)-(p+t)/20-((p+t)%20==0?0:1));
            }
        else
            t=1;
        for(int j=head[x];j!=-1;j=edge[j].next)
        {
            int v=edge[j].v;

            if(d[v]>d[x]+t){
                d[v]=d[x]+t;
            }
        }
    }
}

void road(int st,int ed)
{
    int u=st;
    LL s;
    while(u!=ed)
    {
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].v;
            if(v<26)
                s=d[u]/20+((d[u]%20==0)?0:1);
            else
                s=1;
            if(d[v]==d[u]-s){
                q.push(v);
                u=v;
                break;
            }
        }
    }
    while(!q.empty())
    {
        int v=q.front();q.pop();
        if(v<26)
            printf("-%c",v+'A');
        else
            printf("-%c",v-26+'a');
    }
    printf("\n");
}

int num(char ch)
{
    if('a'<=ch&&ch<='z')
        return (26+ch-'a');
    else
        return (ch-'A');
}

int main()
{
    int n,c,cnt=1;
    char str1[2],str2[2];
    while(~scanf("%d",&n))
    {
        if(n==-1)
            return 0;
        init();
        for(int i=0;i<n;i++)
        {
            scanf("%s%s",str1,str2);
            a[i].l=num(str1[0]);
            a[i].r=num(str2[0]);
        }
        sort(a,a+n,cmp);
        for(int i=0;i<n;i++)
        {
            add(a[i].l,a[i].r);
            add(a[i].r,a[i].l);
        }

        scanf("%d%s%s",&c,str1,str2);
        int x=num(str1[0]);
        int y=num(str2[0]);
        dijkstra(y,c);

        printf("Case %d:\n",cnt++);
        printf("%lld\n",d[x]);
        if(x<26)
            printf("%c",x+'A');
        else
            printf("%c",x-26+'a');
        road(x,y);
    }
    return 0;
}

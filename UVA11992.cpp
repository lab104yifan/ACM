#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000005<<2;
const int inf = 1000005;
int sum[maxn], minv[maxn], maxv[maxn];
int addv[maxn], setv[maxn];
int r, c, q, ql, qr, v;
int t, x1, y1, x2, y2;
int n, ans1, ans2, ans3;
void construct(int o, int l, int r)
{
  sum[o] = minv[o] = maxv[o] = 0;
  addv[o] = setv[o] = 0;
  if(l != r)
  	 {
  	 	int m = (l+r) >> 1;
  	 	construct(2*o, l, m);
  	 	construct(2*o+1, m+1, r);
  	 }
}
void pushup(int o)
{
  sum[o] = sum[2*o] + sum[2*o+1];
  minv[o] = min(minv[2*o], minv[2*o+1]);
  maxv[o] = max(maxv[2*o], maxv[2*o+1]);
}
void pushdown(int o, int l, int r)
{
  if(setv[o])
  	 {
  	   setv[2*o] = setv[2*o+1] = setv[o];
  	   addv[2*o] = addv[2*o+1] = 0;         // 之前就是少了这一步， 一直没过
  	   int m = (l+r) >> 1;
  	   sum[2*o] = setv[o] * (m-l+1);
  	   sum[2*o+1] = setv[o] * (r-m);
  	   minv[2*o] = minv[2*o+1] = setv[o];
  	   maxv[2*o] = maxv[2*o+1] = setv[o];
  	   setv[o] = 0; 
  	 }
  if(addv[o])
    {
      addv[2*o] += addv[o];
      addv[2*o+1] += addv[o];
      int m = (l+r) >> 1;
      sum[2*o] += (m-l+1) * addv[o];
      sum[2*o+1] += (r-m) * addv[o];
      minv[2*o] += addv[o];
      maxv[2*o] += addv[o];
      minv[2*o+1] += addv[o];
      maxv[2*o+1] += addv[o];
      addv[o] = 0;
    }
}
void add(int o, int l, int r)
{
  if(ql<=l && qr>=r)
    {
      addv[o] += v;
      sum[o] += (r-l+1) * v;
      minv[o] += v;
      maxv[o] += v;
      return;
    }
   pushdown(o,  l, r);
   int m = (l+r) >> 1;
   if(ql <= m)
   	 add(2*o,  l, m);
   if(qr > m)
     add(2*o+1, m+1, r);
   pushup(o);
}
void set(int o, int l, int r)
{
  if(ql<=l && qr>=r)
    {
      setv[o] = v;
      sum[o] = v*(r-l+1);
      minv[o] = maxv[o] = v;
      addv[o] = 0;
      return;
    }
   pushdown(o,  l, r);
   int m = (l+r) >> 1;
   if(ql <= m)
   	 set(2*o, l, m);
   if(qr > m)
     set(2*o+1, m+1, r);
   pushup(o);
}
void query(int o, int l, int r)
{
  if(ql<=l && qr>=r)
    {
      ans1 += sum[o];
      ans2 = min(ans2, minv[o]);
      ans3 = max(ans3, maxv[o]);
      return;
    }
  pushdown(o,  l, r);
  int m = (l+r) >> 1;
  if(ql <= m)
  	query(2*o, l, m);
  if(qr > m)
  	query(2*o+1, m+1, r);
}
int main()
{
  while(scanf("%d %d %d", &r, &c, &q) == 3)
  	 {
  	 	n = r*c;
  	 	construct(1, 1, n);
  	 	while(q--)
  	 	  {
  	 	  	 scanf("%d %d %d %d %d", &t, &x1, &y1, &x2, &y2);
  	 	  	 if(t == 1)
  	 	  	   {
  	 	  	   	 scanf("%d", &v);
  	 	  	   	 for(int i=x1; i<=x2; i++)
  	 	  	   	   {
  	 	  	   	   	  ql = (i-1)*c + y1;
  	 	  	   	   	  qr = (i-1)*c + y2;
  	 	  	   	   	  add(1, 1, n);
  	 	  	   	   }
  	 	  	   }
  	 	  	 if(t == 2)
  	 	  	  {
  	 	  	  	 scanf("%d", &v);
  	 	  	  	 for(int i=x1;  i<=x2; i++)
  	 	  	  	   {
  	 	  	  	   	 ql = (i-1)*c + y1;
  	 	  	  	   	 qr = (i-1)*c + y2;
  	 	  	  	   	 set(1, 1, n);
  	 	  	  	   }
  	 	  	  }
  	 	  	if(t == 3)
  	 	  	  {
  	 	  	     ans1 = 0;
  	 	  	     ans2 = inf;
  	 	  	     ans3 = -inf;
  	 	  	     for(int i=x1;  i<=x2; i++)
  	 	  	       {
  	 	  	       	 ql = (i-1)*c + y1;
  	 	  	       	 qr = (i-1)*c + y2;
  	 	  	       	 query(1, 1, n);
  	 	  	       }
  	 	  	     printf("%d %d %d\n", ans1, ans2, ans3);
  	 	  	  }
  	 	  }
  	 }
  return 0;
}

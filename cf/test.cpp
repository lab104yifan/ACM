#include <cstdio>
#include <algorithm>

#define N 100000

using namespace std;

bool rev;
int n,q,beg=1,end,typ,p,l,r,bit[N+10];

inline void add(int x,int y){
	for (;x<=n;x+=x&-x) bit[x]+=y;
}

inline int query(int x){
	int res=0;
	for (;x;x-=x&-x) res+=bit[x];
	return res;
}

int main(){
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;++i) add(i,1);
	end=n;
	for (int i=1;i<=q;++i){
		scanf("%d",&typ);
		if (typ==1){
			scanf("%d",&p);
			if (p<=(end-beg+1)/2)
				if (rev){
					p=end-p;
					for (int j=end;j>p;--j) add(2*p-j+1,query(j)-query(j-1));
					end=p;
				}
				else{
					p+=beg-1;
					for (int j=beg;j<=p;++j) add(2*p-j+1,query(j)-query(j-1));
					beg=p+1;
				}
			else{
				if (rev){
					p=end-p;
					for (int j=beg;j<=p;++j) add(2*p-j+1,query(j)-query(j-1));
					beg=p+1;
				}
				else{
					p+=beg-1;
					for (int j=end;j>p;--j) add(2*p-j+1,query(j)-query(j-1));
					end=p;
				}
				rev^=1;
			}
		}
		else{
			scanf("%d%d",&l,&r);
			if (rev) l=end-l,r=end-r;else l+=beg-1,r+=beg-1;
			if (l>r) swap(l,r);
			printf("%d\n",query(r)-query(l));
		}
		//<debug>
			/*puts("");
			for (int j=beg;j<=end;++j) printf("--");puts("");
			for (int j=beg;j<=end;++j) printf("%d ",query(j)-query(j-1));puts("");
			for (int j=beg;j<=end;++j) printf("--");puts("");
			printf("BEGIN @ %d END @ %d REV %s\n",beg,end,rev?"Y":"N");
			puts("");*/
		//</debug>
	}
	return 0;
}

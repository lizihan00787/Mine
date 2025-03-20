#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
using namespace std;
template<typename P>
void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
	       if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
	   x=res*f;
}
template<typename PP,typename ...Arc>
void read(PP &x,Arc &...y) {read(x),read(y...);}
int T=1;

#define lowbit(x) (x&(-x))

const int N=3e6+20;

int n,m;
int t[N];
struct node{
	int x,y,id;
	bool is;
}a[N];
int cnt=0;
int que[N],ans[N];

bool cmp(node a,node b){
	if(a.x==b.x && a.y==b.y) return a.is<b.is;
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}
void addd(int id,int x,int y,int is){
	a[++cnt].x=x;
	a[cnt].y=y;
	a[cnt].id=id;
	a[cnt].is=is;
	que[cnt]=y;
}

void add(int k,int x) {for(int i=k;i<=cnt;i+=lowbit(i)) t[i]+=x;}
int query(int k) {int res=0;for(int i=k;i;i-=lowbit(i)) res+=t[i];return res;}

signed main(){    
	read(n,m);
	for(int i=1;i<=n;++i){
		int x,y;
		read(x,y);
		addd(i,x,y,0);
	}
	for(int i=1;i<=m;++i){
		int a,b,c,d;
		read(a,b,c,d);
		addd(i,a-1,b-1,1);
		addd(i+m,c,d,1);
		addd(i+2*m,a-1,d,1);
		addd(i+3*m,c,b-1,1);
	}
	sort(a+1,a+cnt+1,cmp);
	sort(que+1,que+cnt+1);
	for(int i=1;i<=cnt;++i){
		int k=lower_bound(que+1,que+cnt+1,a[i].y)-que;
		if(!a[i].is) add(k,1);
		else ans[a[i].id]+=query(k);
	}
	for(int i=1;i<=m;++i){
		int res=ans[i]+ans[i+m]-ans[i+2*m]-ans[i+3*m];
		cout<<res<<endl;
	}
    return 0;
}

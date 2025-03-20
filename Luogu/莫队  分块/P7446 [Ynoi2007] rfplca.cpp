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

const int N=4e5+20;
const int M=4020;

int n,m;
int a[N],fa[N],pa[N];

struct blk{
	int siz,cnt;
	int id[N],cha[N];
	int L[M],R[M];
	ll tag[M];
	void init(){
		cnt=(n-1)/(siz=sqrt(n))+1;
		for(int i=1;i<=n;++i) id[i]=(i-1)/siz+1;
		for(int i=1;i<=cnt;++i){
			L[i]=R[i-1]+1;
			R[i]=i==cnt?n:i*siz;
		}
	}
	#define C(i) (cha[i]<=siz)
	#define Pa(x) (C(id[x]) ? pa[x]:max(1ll,fa[x]-tag[id[x]]))
	#define Fa(x) (C(id[x]) ? fa[x]:max(1ll,fa[x]-tag[id[x]]))
	void upd1(int i){
		if(C(id[i])) pa[i]=id[i]^id[fa[i]]?fa[i]:pa[fa[i]];
	}
	void upd2(int i,int x){
		if(!C(i)) return void(tag[i]=min(tag[i]+x,n*1ll));
		for(int j=L[i];j<=R[i];++i) fa[j]=max(1,fa[j]-x),upd1(j);
	}
	void mod1(int l,int r,int x){
		for(int i=l;i<=r;++i)  fa[i]=max(1,fa[i]-x);
		for(int i=l;i<=R[id[r]];++i) upd1(i);
	}
	void modify(int l,int r,int x){
		if(id[l]==id[r]) return mod1(l,r,x);
		mod1(l,R[id[l]],x);modify(L[id[r]],r,x);
		for(int i=id[l]+1;i<id[r];++i) upd2(i,x),++cha[i];
	}
	int query(int u,int v){
		while(u!=v){
			int pu=Pa(u),pv=Pa(v);
			if(id[pu]!=id[pv]) id[pu]<id[pv]?v=pv:u=pu;
			else if(pu!=pv) pu<pv?v=pv:u=pu;
			else u>v?u=Fa(u):v=Fa(v);
		}
		return u;
	}
}b;

void solve(){
    read(n,m);
	fa[1]=pa[1]=1;
	b.init();
	for(int i=2;i<=n;++i) read(fa[i]),b.upd1(i);
	int op,l,r,las=0;
	while(m--){
		read(op,l,r);
		l^=las,r^=las;
		if(op==1){
			int x;
			read(x);
			b.modify(l,r,x^las);
		}
		else las=b.query(l,r),cout<<las<<endl;
	}
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



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

const int N=1e5+20,M=3e7+20;

int n,m,tot;
ll ans;
int a[N],pos[N],quea[N],queb[N];

int rtt[N];
struct node{
	int ls,rs,val;
}t[M];

#define lson (t[rt].ls)
#define rson (t[rt].rs)
void update(int &rt,int l,int r,int k,int x){
	if(!rt) rt=++tot;
	t[rt].val+=x;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(k<=mid) update(lson,l,mid,k,x);
	else update(rson,mid+1,r,k,x);
}
#define lowbit(x) (x&(-x))
int query(int l,int r,int x,int mode){
	int cnta=0,cntb=0,sum=0,mid;
	for(int i=l-1;i;i-=lowbit(i)) quea[++cnta]=rtt[i];
	for(int i=r;i;i-=lowbit(i)) queb[++cntb]=rtt[i];
	l=1,r=n;
	while(l!=r){
		mid=(l+r)>>1;
		if(x>mid){
			if(mode){
				for(int i=1;i<=cnta;++i) sum-=t[t[quea[i]].ls].val;
				for(int i=1;i<=cntb;++i) sum+=t[t[queb[i]].ls].val;
			}
			for(int i=1;i<=cnta;++i) quea[i]=t[quea[i]].rs;
			for(int i=1;i<=cntb;++i) queb[i]=t[queb[i]].rs;
			l=mid+1;
		}
		else{	
			if(!mode){
				for(int i=1;i<=cnta;++i) sum-=t[t[quea[i]].rs].val;
				for(int i=1;i<=cntb;++i) sum+=t[t[queb[i]].rs].val;
			}
			for(int i=1;i<=cnta;++i) quea[i]=t[quea[i]].ls;
			for(int i=1;i<=cntb;++i) queb[i]=t[queb[i]].ls;
			r=mid;
		}
	}
	return sum;
}

void solve(){
    read(n,m);
	for(int i=1;i<=n;++i){
		read(a[i]);pos[a[i]]=i;
		ans+=query(1,i-1,a[i],0);
		for(int j=i;j<=n;j+=lowbit(j)) update(rtt[j],1,n,a[i],1);
	}
	cout<<ans<<endl;
	for(int i=1;i<m;++i){
		int x;
		read(x);
		ans-=query(1,pos[x]-1,x,0);
		ans-=query(pos[x]+1,n,x,1);
		cout<<ans<<endl;
		for(int j=pos[x];j<=n;j+=lowbit(j)) update(rtt[j],1,n,x,-1);
	}
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



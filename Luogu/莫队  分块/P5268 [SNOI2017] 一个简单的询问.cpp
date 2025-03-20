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

const int N=5e4+20;

int n,m,res,qcnt,l,r,siz;

int a[N],id[N],ans[N];
int cntl[N],cntr[N];
struct node{
	int l,r,id,f;
	node(int l=0,int r=0,int id=0,int f=0):l(l),r(r),id(id),f(f){}
}q[N<<2];

bool cmp(node a,node b){
	if(id[a.l]==id[b.l]) return a.r<b.r;
	return a.l<b.l;
}

void movel(int x){
	if(x==1){
		++cntl[a[l+1]];
		res+=cntr[a[l+1]];
		l++;
	}
	else{
		--cntl[a[l]];
		res-=cntr[a[l]];
		l--;
	}
}
void mover(int x){
	if(x==1){
		++cntr[a[r+1]];
		res+=cntl[a[r+1]];
		r++;
	}
	else{
		--cntr[a[r]];
		res-=cntl[a[r]];
		r--;
	}
}

void solve(){
    read(n);
	int l1,l2,r1,r2;
	siz=sqrt(n);
	for(int i=1;i<=n;++i) read(a[i]),id[i]=(i-1)/siz+1;
	read(m);
	for(int i=1;i<=m;++i){
		read(l1,r1,l2,r2);
		q[++qcnt]=node(r1,r2,i,1);
		q[++qcnt]=node(r1,l2-1,i,-1);
		q[++qcnt]=node(l1-1,r2,i,-1);
		q[++qcnt]=node(l1-1,l2-1,i,1);
	}
	for(int i=1;i<=n;++i) if(q[i].l>q[i].r) swap(q[i].l,q[i].r);
	sort(q+1,q+qcnt+1,cmp);
	l=0,r=0;
	for(int i=1;i<=qcnt;++i){
		while(l<q[i].l) movel(1);
		while(l>q[i].l) movel(-1);
		while(r<q[i].r) mover(1);
		while(r>q[i].r) mover(-1);
		if(q[i].f==1) ans[q[i].id]+=res;
		else ans[q[i].id]-=res;
	}
	for(int i=1;i<=m;++i) cout<<ans[i]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



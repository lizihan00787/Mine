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

const int N=5e4+200,mod=201314;

int n,m,tot=0;
int fa[N],siz[N],son[N],tp[N],dfx[N];

vector<int> g[N];
vector<int> pl[N],ml[N];
int ask[N];
int ans[N];

struct Stree{
	#define lson (rt<<1)
	#define rson (rt<<1|1)
	struct node{
		int sum,tag;
	}t[N<<2];
	void pushup(int rt){
		t[rt].sum=t[rson].sum+t[lson].sum;
	}
	void pushdown(int rt,int l,int r){
		int mid=(l+r)>>1;
		if(t[rt].tag){
			t[lson].tag=(t[lson].tag+t[rt].tag+mod)%mod;
			t[rson].tag=(t[rson].tag+t[rt].tag+mod)%mod;
			t[lson].sum=(t[lson].sum+t[rt].tag*(mid-l+1)%mod+mod)%mod;
			t[rson].sum=(t[rson].sum+t[rt].tag*(r-mid)%mod+mod)%mod;
			t[rt].tag=0;
		}
	}
	void update(int rt,int l,int r,int L,int R,int k){
		if(L<=l && r<=R){
			t[rt].sum=(t[rt].sum+k*(r-l+1)%mod+mod)%mod;
			t[rt].tag=(t[rt].tag+k+mod)%mod;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(rt,l,r);
		if(L<=mid) update(lson,l,mid,L,R,k);
		if(R>mid) update(rson,mid+1,r,L,R,k);
		pushup(rt);
	}
	int query(int rt,int l,int r,int L,int R){
		if(L<=l && r<=R) return t[rt].sum;
		pushdown(rt,l,r);
		int mid=(l+r)>>1,res=0;
		if(L<=mid) res+=query(lson,l,mid,L,R);
		if(R>mid) res+=query(rson,mid+1,r,L,R);
		return res;
	}
}Q;
void modi(int x){
	while(x){
		Q.update(1,1,n,dfx[tp[x]],dfx[x],1);
		x=fa[tp[x]];
	}
}
int que(int x){
	int res=0;
	while(x){
		res=(res+Q.query(1,1,n,dfx[tp[x]],dfx[x])%mod+mod)%mod;
		x=fa[tp[x]];
	}
	return res;
}

void dfs1(int u){
	siz[u]=1;
	for(auto to:g[u]){
		if(to==fa[u]) continue;
		dfs1(to);
		siz[u]+=siz[to];
		if(siz[to]>siz[son[u]]) son[u]=to;
	}
}
void dfs2(int u,int t){
	tp[u]=t;
	dfx[u]=++tot;
	if(son[u]) dfs2(son[u],t);
	for(auto to:g[u]){
		if(to==fa[u] || to==son[u]) continue;
		dfs2(to,to);
	}
}


void solve(){
    read(n),read(m);
	for(int i=2;i<=n;++i) read(fa[i]),g[++fa[i]].push_back(i);
	dfs1(1);
	dfs2(1,1);
	int l,r;
	for(int i=1;i<=m;++i){
		read(l),read(r),read(ask[i]);
		ml[l].push_back(i);pl[r+1].push_back(i);
		++ask[i];
	}
	for(int i=1;i<=n;++i){
		modi(i);
		for(int it:pl[i]) ans[it]+=que(ask[it]);
		for(int it:ml[i]) ans[it]-=que(ask[it]);
	}
	for(int i=1;i<=m;++i) cout<<(ans[i]+mod)%mod<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



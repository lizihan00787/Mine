#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
#define fi first
#define se second
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
template<typename PP>
void write(PP x) {if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar(x%10+'0');}

int T=1;

const int N=1e5+20;

set<int> st;
vector<PII> g[N],ln[N],qr[N];
int n,q;
int dep[N],siz[N],son[N],col[N],tot,ans[N],pos[N];

namespace BIT{
	#define lowbit(x) (x&(-x))
	int t[N];
	void add(int x,int val) {for(;x<=n;x+=lowbit(x)) t[x]+=val;}
	int query(int x) {int res=0;for(;x;x-=lowbit(x)) res+=t[x];return res;}
}
using namespace BIT;

void dfs(int u,int fa){
	siz[u]=1;
	for(auto to:g[u]){
		if(to.fi==fa) continue;
		dep[to.fi]=dep[u]+to.se;
		dfs(to.fi,u);
		siz[u]+=siz[to.fi];
		if(siz[to.fi]>siz[son[u]]) son[u]=to.fi;
	}
}

int pre(int x) {auto it=st.lower_bound(x);if(it==st.begin()) return 0;return *(--it);}
int nxt(int x) {auto it=st.upper_bound(x);if(it==st.end()) return 0;return *it;}

void find(int u,int c){
	int pp=pre(u);if(pp) ln[pp].emplace_back(u,c);
	int qq=nxt(u);if(qq) ln[u].emplace_back(qq,c);
}
void calc(int u,int fa,int c){
	find(u,c);
	for(auto to:g[u]) if(to.fi!=fa) calc(to.fi,u,c);
}
void ad(int u,int fa){
	st.emplace(u);
	for(auto to:g[u]) if(to.fi!=fa) ad(to.fi,u);
}
void dsu(int u,int fa,bool op){
	for(auto to:g[u]) if(to.fi!=fa && to.fi!=son[u]) dsu(to.fi,u,1);
	if(son[u]) dsu(son[u],u,0);
	find(u,col[u]);
	st.emplace(u);
	for(auto to:g[u]) if(to.fi!=fa && to.fi!=son[u]) calc(to.fi,u,col[u]),ad(to.fi,u);
	if(op) st.clear();
}

void solve(){
    read(n,q);
	for(int i=1;i<n;++i){
		int u,v,w;
		read(u,v,w);
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
	dfs(1,0);
	for(int i=1;i<=n;++i) col[i]=dep[i];
	stable_sort(dep+1,dep+n+1);
	tot=unique(dep+1,dep+n+1)-dep-1;
	for(int i=1;i<=n;++i) col[i]=lower_bound(dep+1,dep+n+1,col[i])-dep;
	dsu(1,0,0);
	for(int i=1;i<=tot;++i) pos[i]=n+1;
	for(int i=1;i<=n;++i) ln[i].emplace_back(i,col[i]);
	for(int i=1,u,v;i<=q;++i) read(u,v),qr[u].emplace_back(v,i);
	for(int i=n;i>=1;--i){
		for(auto it:ln[i]){
			add(pos[it.se],-1);
			pos[it.se]=min(pos[it.se],it.fi);
			add(pos[it.se],1);
		}
		for(auto it:qr[i]) ans[it.se]=query(it.fi);
	}
	for(int i=1;i<=q;++i) write(ans[i]),puts("");
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



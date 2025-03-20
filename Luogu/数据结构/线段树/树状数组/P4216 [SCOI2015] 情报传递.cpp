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

const int N=2e5+20;

int n,m;
int s[N];
vector<int> g[N];
int f[N],siz[N],son[N],tp[N],dep[N],dfx[N],tot;

void dfs1(int u){
	siz[u]=1;
	dep[u]=dep[f[u]]+1;
	dfx[u]=++tot;
	for(auto to:g[u]){
		if(to==f[u]) continue;
		dfs1(to);
		siz[u]+=siz[to];
		if(siz[son[u]]<siz[to]) son[u]=to;
	}
}
void dfs2(int u,int t){
	tp[u]=t;
	if(son[u]) dfs2(son[u],t);
	for(auto to:g[u]){
		if(to==f[u] || to==son[u]) continue;
		dfs2(to,to);
	}
}
int lca(int a,int b){
    while(tp[a]!=tp[b]){
        if(dep[tp[a]]<dep[tp[b]]) swap(a,b);
        a=f[tp[a]];
    }
    if(dep[a]<dep[b]) swap(a,b);
    return b;
}
int dis(const int &u,const int &v){
	return dep[u]+dep[v]-(dep[lca(u,v)]<<1)+1;
}

struct Stree{
	int BIT[N];
	inline void Add(int x,const int&val){
		for(;x<=n;x+=1<<__builtin_ctz(x))BIT[x]+=val;
	}
	inline int Query(int x){
		int ans=0;
		for(;x>=1;x-=1<<__builtin_ctz(x))ans+=BIT[x];
		return ans;
	}
	inline int que(const int&x,const int&y){
		int lc=lca(x,y);
		return Query(dfx[x])+Query(dfx[y])-Query(dfx[lc])-Query(dfx[f[lc]]);
	}
}Q;

int opt[N],x[N],y[N],ans[N];
vector<int> id[N];

void solve(){
	register int i,k;
    read(n);
	for(i=1;i<=n;++i) read(f[i]),g[f[i]].push_back(i);
	for(i=1;f[i];i=f[i]);
	dfs1(i);
	dfs2(i,i);
	read(m);
	for(i=1;i<=m;++i){
		read(opt[i]);
		if(opt[i]==1){
			read(x[i],y[i],k);
			if(k<i) id[i-k-1].push_back(i);
		}
		if(opt[i]==2) read(x[i]);
	}
	for(i=1;i<=m;++i){
		if(opt[i]==2){
			Q.Add(dfx[x[i]],1);
			Q.Add(dfx[x[i]]+siz[x[i]],-1);
		}
		for(int &it:id[i]) ans[it]=Q.que(x[it],y[it]);
		if(opt[i]==1) cout<<dis(x[i],y[i])<<' '<<ans[i]<<endl;
	}
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



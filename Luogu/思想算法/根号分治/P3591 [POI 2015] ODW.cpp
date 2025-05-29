#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
template<typename P>
inline void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=5e4+20,w=25;

int n;
int a[N],b[N],c[N];
vector<int> g[N];
int cnt;
int siz[N],son[N],tp[N],f[N],dep[N],dfx[N],rk[N],sum[N][30];

void dfs1(int u,int fa){
    siz[u]=1;
    dep[u]=dep[fa]+1;
    f[u]=fa;
    for(auto to:g[u]){
        if(to==fa) continue;
        dfs1(to,u);
        siz[u]+=siz[to];
        if(siz[to]>siz[son[u]]) son[u]=to;
    }
}
void dfs2(int u,int t){
    tp[u]=t;
    dfx[u]=++cnt;
    rk[cnt]=u;
    for(int i=1,p=f[u];i<=w;++i,p=f[p]) sum[u][i]=sum[p][i]+a[u];
    if(son[u]) dfs2(son[u],t);
    for(auto to:g[u]){
        if(to==f[u] || to==son[u]) continue;
        dfs2(to,to);
    }
}
int jump(int x,int k){
    while(k>=dfx[x]-dfx[tp[x]]+1 && x!=1){
        k-=(dfx[x]-dfx[tp[x]]+1);
        x=f[tp[x]];
    }
    if(k>dfx[x]) return 0;
    return rk[dfx[x]-k];
}
int lca(int x,int y){
    while(tp[x]!=tp[y]){
        if(dep[tp[x]]<dep[tp[y]]) swap(x,y);
        x=f[tp[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    return y;
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<n;++i){
        int u,v;
        read(u,v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;++i) read(b[i]);
    for(int i=1;i<n;++i) read(c[i]);
    for(int i=2;i<=n;++i){
        int x=b[i-1],y=b[i],k=c[i-1];
        int lc=lca(x,y);
        int res=0;
        if(k<=w){
			res+=sum[x][k]-sum[jump(x,k*((dep[x]-dep[lc])/k+1))][k];
			y=jump(y,(dep[x]+dep[y]-2*dep[lc])%k);
			res+=sum[y][k]-sum[jump(y,k*((dep[y]-dep[lc])/k+1))][k];
        }
        else{
            for(int i=x;dep[i]>=dep[lc];i=jump(i,k)) res+=a[i];
            y=jump(y,(dep[x]+dep[y]-2*dep[lc])%k);
            for(int i=y;dep[i]>=dep[lc];i=jump(i,k)) res+=a[i];
        }
        if((dep[x]-dep[lc])%k==0 && (dep[y]-dep[lc])%k==0) res-=a[lc];
        cout<<res<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
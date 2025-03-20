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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=5e5+10;

int n,m,s;
vector<int> g[N];
int siz[N],dep[N],son[N],tp[N],f[N];
void dfs1(int u,int fa){
    siz[u]=1;
    f[u]=fa;
    dep[u]=dep[fa]+1;
    for(auto to:g[u]){
        if(to==fa) continue;
        dfs1(to,u);
        siz[u]+=siz[to];
        if(siz[to]>siz[son[u]]) son[u]=to;
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

signed main(){
    auto solve=[&](){
        read(n),read(m),read(s);
        for(int i=1;i<n;++i){
            int u,v;
            read(u),read(v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs1(s,s);
        dfs2(s,0);
        for(int i=1;i<=m;++i){
            int u,v;
            read(u),read(v);
            if(u==v) cout<<u<<endl;
            else cout<<lca(u,v)<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
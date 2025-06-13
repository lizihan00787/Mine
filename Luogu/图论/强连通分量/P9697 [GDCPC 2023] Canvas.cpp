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

const int N=5e5+20;

int n,m;
vector<tuple<int,int> > G[N];
struct oper{
    int l,x,r,y;
}op[N];

int dfx[N],st[N],low[N],see[N],tim,tp,scc,bel[N];
void tarjan(int u){
    dfx[u]=low[u]=++tim;
    st[++tp]=u,see[u]=1;
    for(auto [v,id]:G[u]){
        if(!dfx[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(see[v]) low[u]=min(low[u],dfx[v]);
    }
    if(dfx[u]==low[u]){
        scc++;bel[u]=u;
        while(st[tp]!=u){
            bel[st[tp]]=u;
            see[st[tp]]=0;
            --tp;
        }
        see[st[tp]]=0;tp--;
    }
}

vector<int> ans,aft;
int two[N],vis[N],deg[N],res[N];

void dfs(int u){
    vis[u]=1;
    for(auto [v,id]:G[u]){
        ans.emplace_back(id);
        if(!vis[v]) dfs(v);
    }
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=m;++i){
        read(op[i].l,op[i].x,op[i].r,op[i].y);
        if(op[i].x==2 && op[i].y==2) ans.emplace_back(i),two[op[i].l]=two[op[i].r]=1;
        else if(op[i].x==1 && op[i].y==1) aft.emplace_back(i);
        else{
            if(op[i].x>op[i].y) swap(op[i].l,op[i].r),swap(op[i].x,op[i].y);
            G[op[i].l].emplace_back(op[i].r,i);
        }
    }
    for(int i=1;i<=n;++i) if(!dfx[i]) tarjan(i);
    for(int u=1;u<=n;++u) for(auto [v,id]:G[u]) if(bel[u]!=bel[v]) ++deg[bel[v]];
    for(int u=1;u<=n;++u) if(!deg[bel[u]] && !vis[u] && two[u]) dfs(u);
    for(int u=1;u<=n;++u) if(!deg[bel[u]] && !vis[u]) dfs(u);
    for(int i:aft) ans.emplace_back(i);
    reverse(ans.begin(),ans.end());
    for(int i:ans) res[op[i].l]=op[i].x,res[op[i].r]=op[i].y;
    cout<<accumulate(res+1,res+n+1,0)<<endl;
    for(int i:ans) cout<<i<<' ';cout<<endl;
    auto clear=[&](){
        for(int i=1;i<=n;++i) G[i].clear(),dfx[i]=low[i]=see[i]=bel[i]=vis[i]=deg[i]=res[i]=two[i]=0;
        tim=tp=scc=0;
        ans.clear();
        aft.clear();
    };
    clear();
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}
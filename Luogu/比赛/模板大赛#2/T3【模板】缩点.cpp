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

const int N=1e4+10,Max=1e5+10;

int n,m;
int w[N],we[N];
struct edge{
    int u,to;
}e[Max<<1];
vector<int> g[N],ge[N];

int dfx[N],low[N],scc[N],col=0,num=0,tp=0;
bool vis[N];
int st[N];
int dis[N],in[N];

void tanjan(int u){
    dfx[u]=low[u]=++num;
    st[++tp]=u;vis[u]=1;
    for(int to:g[u]){
        if(!dfx[to]) tanjan(to),low[u]=min(low[to],low[u]);
        else if(vis[to]) low[u]=min(low[u],dfx[to]);
    }
    if(low[u]==dfx[u]){
        ++col;
        scc[u]=u;
        while(st[tp]!=u){
            scc[st[tp]]=u;
            w[u]+=w[st[tp]];
            vis[st[tp]]=0;
            --tp;
        }
        vis[st[tp]]=0;
        tp--;
    }
}

void topo(){
    queue<int> q;
    for(int i=1;i<=n;++i) if(!in[i] && scc[i]==i) q.push(i),dis[i]=w[i];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto to:ge[u]){
            dis[to]=max(dis[to],dis[u]+w[to]);
            if(--in[to]==0) q.push(to);
        }
    }
    int ans=0;
    for(int i=1;i<=n;++i) ans=max(ans,dis[i]);
    cout<<ans<<endl;
}

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(w[i]);
        for(int i=1;i<=m;++i){
            int u,v;
            read(u),read(v);
            e[i].u=u,e[i].to=v;
            g[u].push_back(v);
        }
        for(int i=1;i<=n;++i) if(!dfx[i]) tanjan(i);
        for(int i=1;i<=m;++i){
            int u=scc[e[i].u],v=scc[e[i].to];
            if(u!=v){
                ge[u].push_back(v);
                in[v]++;
            }
        }
        topo();
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
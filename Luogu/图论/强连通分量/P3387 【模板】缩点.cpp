#include<bits/stdc++.h>
#define int long long
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int Max=1e5+10,N=1e4+10;
int n,m;
struct edge{
    int to,nxt,u;
}e[Max<<1],ed[Max<<1];
int head[N],cnt=0,h[N],s=0;
void add(int u,int v){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    e[cnt].u=u;
    head[u]=cnt;
}
int dfx[N],low[N],st[N],tp,scc[N],num=0,col=0;
int a[N];
bool vis[N];
void tarjan(int u){
    dfx[u]=low[u]=++num;
    st[++tp]=u;vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int to=e[i].to;
        if(!dfx[to]){
            tarjan(to);
            low[u]=min(low[u],low[to]);
        }
        else if(vis[to]){
            low[u]=min(low[u],dfx[to]);
        }
    }
    if(low[u]==dfx[u]){
        col++;
        scc[u]=u;
        while(st[tp]!=u){
            scc[st[tp]]=u;
            a[u]+=a[st[tp]];
            vis[st[tp]]=0;
            --tp;
        }
        vis[st[tp]]=0;
        --tp;
    }
}
int dis[N];
int in[N];
int topo(){
    queue<int> q;
    for(int i=1;i<=n;++i) if(!in[i] && scc[i]==i) q.push(i),dis[i]=a[i];
    int ans=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=h[u];i;i=ed[i].nxt){
            int to=ed[i].to;
            dis[to]=max(dis[to],dis[u]+a[to]);
            in[to]--;
            if(in[to]==0) q.push(to);
        }
    }
    for(int i=1;i<=n;++i) ans=max(ans,dis[i]);
    return ans;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);   
        for(int i=1;i<=n;++i) read(a[i]);
        for(int i=1;i<=m;++i){
            int u,v;
            read(u),read(v);
            add(u,v);
        }
        for(int i=1;i<=n;++i) if(!dfx[i]) tarjan(i);
        for(int i=1;i<=m;++i){
            int u=scc[e[i].u],to=scc[e[i].to];
            if(u!=to){
                ed[++s]={to,h[u],u};
                h[u]=s;
                in[to]++;
            }
        }
        cout<<topo()<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
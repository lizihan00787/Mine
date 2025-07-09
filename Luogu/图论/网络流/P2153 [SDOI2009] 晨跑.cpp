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

const int N=500,M=1e6+20;
const int inf=0x3f3f3f3f;

int n,m,s,t;

namespace MCMF{
    bool vis[N];
    int dis[N],pre[N],flow[N],maxf,minc;
    struct edge{
        int to,nxt,flow,w;
    }e[M<<1];
    int head[N],cnt=1;
    queue<int> q;
    void add(int u,int v,int f,int w){
        e[++cnt]={v,head[u],f,w};head[u]=cnt;
        e[++cnt]={u,head[v],0,-w};head[v]=cnt;
    }
    bool SPFA(int s,int t){
        memset(dis,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        q.push(s),vis[s]=1,dis[s]=0,flow[s]=1<<30;
        while(!q.empty()){
            auto u=q.front();
            q.pop();
            vis[u]=0;
            for(int i=head[u];i;i=e[i].nxt){
                int to=e[i].to,w=e[i].w,f=e[i].flow;
                if(f>0 && dis[to]>dis[u]+w){
                    dis[to]=dis[u]+w;
                    pre[to]=i;
                    flow[to]=min(flow[u],f);
                    if(!vis[to]){
                        vis[to]=1;
                        q.push(to);
                    }
                }
            }
        }
        if(dis[t]==0x3f3f3f3f) return 0;
        return 1;
    }
    void mcmf(){
        while(SPFA(s,t)){
            int now=t;
            maxf+=flow[t];
            minc+=flow[t]*dis[t];
            int p;
            while(now!=s){
                p=pre[now];
                e[p].flow-=flow[t];
                e[p^1].flow+=flow[t];
                now=e[p^1].to;
            }
        }
    }
}
using namespace MCMF;

inline void solve(){
    read(n,m);
    for(int i=1;i<=m;++i){
        int u,v,c;
        read(u,v,c);
        add(u+n,v,1,c);
    }
    for(int i=1;i<=n;++i) add(i,i+n,1,0);
    s=1+n,t=n;
    mcmf();
    cout<<maxf<<' '<<minc<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
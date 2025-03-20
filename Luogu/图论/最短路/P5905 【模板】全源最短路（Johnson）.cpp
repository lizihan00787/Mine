#include<bits/stdc++.h>
#define endl '\n'
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
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=5e3+20,inf=1e9;

int n,m;

struct edge{
    int to,nxt,w;
}e[N<<1];
struct node{
    int to,dis;
    bool operator < (const node &a)const{
        return a.dis<dis;
    }
};
int head[N],cnt=0;
void add(int u,int v,int w){
    e[++cnt].nxt=head[u];
    e[cnt].w=w;
    e[cnt].to=v;
    head[u]=cnt;
}

int h[N],in[N],dis[N];
bool vis[N];

bool SPFA(int s){
    queue<int> q;
    memset(h,63,sizeof(h));
    h[s]=0;
    vis[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(h[u]+e[i].w<h[to]){
                h[to]=h[u]+e[i].w;
                if(!vis[to]){
                    vis[to]=1;
                    q.push(to);
                    in[to]++;
                    if(in[to]==n+1) return 0;
                }
            }
        }
    }
    return 1;
}
void dijkstra(int s){
    priority_queue<node> q;
    for(int i=1;i<=n;++i) dis[i]=inf;
    memset(vis,0,sizeof(vis));
    dis[s]=0;
    q.push({s,0});
    while(!q.empty()){
        int u=q.top().to;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(dis[to]>dis[u]+e[i].w){
                dis[to]=dis[u]+e[i].w;
                if(!vis[to]) q.push({to,dis[to]});
            }
        }
    }
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=m;++i){
        int u,v,w;
        read(u,v,w);
        add(u,v,w);
    }
    for(int i=1;i<=n;++i) add(0,i,0);
    if(!SPFA(0)) {puts("-1");return;}
    for(int u=1;u<=n;++u){
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            e[i].w+=h[u]-h[to];
        }
    }
    for(int u=1;u<=n;++u){
        dijkstra(u);
        int ans=0;
        for(int v=1;v<=n;++v){
            if(dis[v]==inf) ans+=v*inf;
            else ans+=v*(dis[v]-h[u]+h[v]);
        }
        cout<<ans<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
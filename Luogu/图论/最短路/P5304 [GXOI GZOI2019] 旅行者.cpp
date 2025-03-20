#include<bits/stdc++.h>
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

const int N=1e5+10,Max=5e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,k;
int a[N];
bool isc[N];
int X[Max],Y[Max],W[Max];
struct edge{
    int to,nxt,w;
}e[Max<<1];
int head[N],cnt=0;
void add(int u,int v,int w){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    e[cnt].w=w;
    head[u]=cnt;
}

bool vis[N];
int col[2][N];
ll dis[2][N];
struct node{
    int to;
    ll dis;
    bool operator < (const node &a)const{
        return dis>a.dis;
    }
};
void dijkstra(ll *dis,int *col){
    priority_queue<node> q;
    for(int i=1;i<=n;++i) dis[i]=inf;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=k;++i) col[a[i]]=a[i],q.push({a[i],0}),dis[a[i]]=0;
    while(!q.empty()){
        auto it=q.top();
        q.pop();
        int u=it.to;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(dis[to]>dis[u]+e[i].w){
                dis[to]=dis[u]+e[i].w;
                q.push({to,dis[to]});
                col[to]=col[u];
            }
        }
    }
}

signed main(){
    auto solve=[&](){
        read(n),read(m),read(k);
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            if(u!=v) add(u,v,w);
            X[i]=u,Y[i]=v,W[i]=w;
        }
        for(int i=1;i<=k;++i) read(a[i]),isc[a[i]]=1;
        dijkstra(dis[0],col[0]);
        for(int i=1;i<=n;++i) head[i]=0;
        cnt=0;
        for(int i=1;i<=m;++i) if(X[i]!=Y[i]) add(Y[i],X[i],W[i]);
        dijkstra(dis[1],col[1]);
        ll ans=inf;
        for(int i=1;i<=m;++i){
            int x=X[i],y=Y[i],w=W[i];
            if(col[0][x] && col[1][y] && col[0][x]!=col[1][y]) ans=min(ans,dis[0][x]+dis[1][y]+w);
        }
        cout<<ans<<endl;
        for(int i=1;i<=n;++i) head[i]=0,isc[i]=0;
        cnt=0;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}
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

const int N=1e5+20,M=2e5+20;

struct node{
    int nxt,v,w,flow;
}e[M<<1];
int dis[N],pre[N],flow[N],maxf,maxc,cnt=1,head[N],s,t;
bool vis[N];
void clear(){
    for(int i=1;i<=cnt;++i) e[i].w=e[i].flow=e[i].nxt=e[i].v=0;
    memset(head,0,sizeof(head));
    maxc=maxf=0;
    cnt=1;
}
void add(int u,int v,int f,int w){
    e[++cnt]=(node){head[u],v,-w,f};head[u]=cnt;
    e[++cnt]=(node){head[v],u,w,0};head[v]=cnt;
}

bool SPFA(int s,int t){
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    q.push(s),vis[s]=1,dis[s]=0,flow[s]=1<<30;
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].v,w=e[i].w,f=e[i].flow;
            if(f>0 && dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                pre[v]=i;
                flow[v]=min(flow[u],f);
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
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
        maxc+=flow[t]*dis[t];
        int p;
        while(now!=s){
            p=pre[now];
            e[p].flow-=flow[t];
            e[p^1].flow+=flow[t];
            now=e[p^1].v;
        }
    }
}
        

int n,m,idx=-1,id[25][55];
int a[25][55];

inline void solve(){
    read(m,n);
    int o=(2*m+n-1)*n/2;
    s=++idx,t=++idx;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m+i-1;++j)
            read(a[i][j]),id[i][j]=++idx;
    for(int i=1;i<=m;++i) add(s,id[1][i],1,0);
    for(int i=1;i<n;++i)
        for(int j=1;j<=m+i-1;++j){
            add(id[i][j],id[i][j]+o,1,a[i][j]);
            add(id[i][j]+o,id[i+1][j],1,0);
            add(id[i][j]+o,id[i+1][j+1],1,0);
        }
    for(int i=1;i<=m+n-1;++i) add(id[n][i],id[n][i]+o,1,a[n][i]),add(id[n][i]+o,t,1,0);
    mcmf();
    cout<<-maxc<<endl;
    clear();

    for(int i=1;i<=m;++i) add(s,id[1][i],1,0);
    for(int i=1;i<n;++i)
        for(int j=1;j<=m+i-1;++j)
            add(id[i][j],id[i+1][j],1,a[i][j]),add(id[i][j],id[i+1][j+1],1,a[i][j]);
    for(int i=1;i<=n+m-1;++i) add(id[n][i],t,0x3f3f3f3f,a[n][i]);
    mcmf();
    cout<<-maxc<<endl;
    clear();

    for(int i=1;i<=m;++i) add(s,id[1][i],1,0);
    for(int i=1;i<n;++i)
        for(int j=1;j<=m+i-1;++j)
            add(id[i][j],id[i+1][j],0x3f3f3f3f,a[i][j]),add(id[i][j],id[i+1][j+1],0x3f3f3f3f,a[i][j]);
    for(int i=1;i<=n+m-1;++i) add(id[n][i],t,0x3f3f3f3f,a[n][i]);
    mcmf();
    cout<<-maxc<<endl;
    clear();
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
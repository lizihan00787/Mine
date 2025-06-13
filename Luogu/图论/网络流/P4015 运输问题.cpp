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

const int N=120,M=1e4+20;
const int inf=0x3f3f3f3f;

bool vis[N];
int co[N][N],a[N],b[N];
int n,m,s,t,dis[N],pre[N],flow[N],maxf,minc;
struct edge{
    int to,nxt,w,flow;
}e[M<<1],ed[M<<1];
int head[N],cnt=1;

void add(int u,int v,int f,int w){
    e[++cnt].flow=f;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    e[cnt].to=v;
    head[u]=cnt;
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
signed main(){
    auto solve=[&](){
        auto buildedge=[&](int op){
            for(int i=1;i<=m;++i) add(s,i,a[i],0),add(i,s,0,0);
            for(int i=1;i<=m;++i)
                for(int j=1;j<=n;++j)
                    add(i,j+m,0x3f3f3f3f,co[i][j]*op),add(j+m,i,0,-co[i][j]*op);
            for(int i=1;i<=n;++i) add(i+m,t,b[i],0),add(t,i+m,0,0);
        };
        read(m,n);
        s=0,t=n+m+1;
        for(int i=1;i<=m;++i) read(a[i]);
        for(int i=1;i<=n;++i) read(b[i]);
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
                read(co[i][j]);
            }
        }
        buildedge(1);
        mcmf();
        cout<<minc<<endl;
        maxf=minc=0;
        cnt=1;
        memset(head,0,sizeof(head));
        buildedge(-1);
        mcmf();
        cout<<-minc<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
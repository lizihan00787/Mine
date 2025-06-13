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

const int N=300,M=1e5+20;

struct edge{
    int to,nxt,w,flow;
}e[M<<1];
int dis[N],pre[N],flow[N],maxf,minc,cnt=1,head[N],s,t;
bool vis[N];

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

int n,m,a,b,idx=0;
int id[20][20];

inline void solve(){
    read(a,b,n,m);
    s=++idx,t=++idx;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=m;++j)
            id[i][j]=++idx;
    for(int i=0;i<=n;++i)
        for(int j=0,w;j<m;++j){
            read(w);
            add(id[i][j],id[i][j+1],1,-w);add(id[i][j+1],id[i][j],0,w);
            add(id[i][j],id[i][j+1],0x3f3f3f3f,0);add(id[i][j+1],id[i][j],0,0);
        }
    for(int j=0;j<=m;++j)
        for(int i=0,w;i<n;++i){
            read(w);
            add(id[i][j],id[i+1][j],1,-w);add(id[i+1][j],id[i][j],0,w);
            add(id[i][j],id[i+1][j],0x3f3f3f3f,0);add(id[i+1][j],id[i][j],0,0);
        }
    while(a--){
        int x,y,w;
        read(w,x,y);
        add(s,id[x][y],w,0);
        add(id[x][y],s,0,0);
    }
    while(b--){
        int x,y,w;
        read(w,x,y);
        add(id[x][y],t,w,0);
        add(t,id[x][y],0,0);
    }
    mcmf();
    cout<<-minc<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
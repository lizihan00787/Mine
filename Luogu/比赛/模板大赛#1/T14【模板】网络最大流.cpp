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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;

int n,m,s,t;
struct edge{
    int to,nxt,w,flow;
}e[N<<1];
int head[N],cnt=1;
void add(int u,int v,int flow,int w){
    e[++cnt].flow=flow;
    e[cnt].w=w;
    e[cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}

bool vis[N];
int dis[N],pre[N],flow[N],maxf,minc;
queue<int> q;

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
    if(dis[t]==inf) return 0;
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
        read(n),read(m),read(s),read(t);
        for(int i=1;i<=m;++i){
            int u,v,f;
            read(u),read(v),read(f);
            add(u,v,f,0);
            add(v,u,0,0);
        }
        mcmf();
        cout<<maxf<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
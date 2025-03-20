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

const int N=1e4+20;
const int Max=5e4+20;

int n,m,k;
int s,t;
struct edge{
    int to,nxt,w;
}e[Max<<6];
int head[N<<5],cnt=0;

void add(int u,int v,int w){
    e[++cnt].w=w;
    e[cnt].to=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}

struct node{
    int to;
    ll dis;
    bool operator < (const node &a)const{
        return dis>a.dis;
    }
};
bool vis[N<<5];
int dis[N<<5];
void dijkstra(int s){
    priority_queue<node> q;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    q.push({s,0});
    dis[s]=0;
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
            }
        }
    }
}

signed main(){
    auto solve=[&](){
        read(n),read(m),read(k);
        read(s),read(t);
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            add(u,v,w);
            add(v,u,w);
            for(int j=1;j<=k;++j){
                add(u+(j-1)*n,v+n*j,0);
                add(v+(j-1)*n,u+n*j,0);
                add(v+n*j,u+n*j,w);
                add(u+n*j,v+n*j,w);
            }
        }
        for(int i=1;i<=k;++i) add(t+(i-1)*n,t+i*n,0);
        dijkstra(s);
        int ans=0x3f3f3f3f;
        for(int i=1;i<=k+1;++i){
            ans=min(ans,dis[t+(i-1)*n]);
        }
        cout<<ans<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
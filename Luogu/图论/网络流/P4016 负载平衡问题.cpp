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

const int N=5010,M=50010,inf=0x3f3f3f3f;

int n;
int a[N];
int sum;
int flow=0,cost=0,s,t,pre[N],dis[N],vis[N],incf[N];

struct node{
    int v,nxt,f,w;
}G[M<<1];
int head[N],cnt=1;

bool SPFA(){
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    q.push(s);
    vis[s]=1;dis[s]=0;
    incf[s]=(1<<30);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=head[u];i;i=G[i].nxt){
            int v=G[i].v,f=G[i].f,w=G[i].w;
            if(!f) continue;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                incf[v]=min(incf[u],f);
                pre[v]=i;
                if(!vis[v]) vis[v]=1,q.push(v);
            }
        }
    }if(dis[t]==0x3f3f3f3f) return 0;
    return 1;
}

inline void mcmf(){
    while(SPFA()){
        int x=t;
        flow+=incf[t];
        cost+=dis[t]*incf[t];
        int i;
        while(x!=s){
            i=pre[x];
            G[i].f-=incf[t];
            G[i^1].f+=incf[t];
            x=G[i^1].v;
        }
    }
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]),sum+=a[i];
    sum/=n;
    auto add=[&](int u,int v,int f,int w){
        G[++cnt].v=v;
        G[cnt].nxt=head[u];
        G[cnt].f=f;
        G[cnt].w=w;
        head[u]=cnt;
    };
    for(int i=1;i<=n;++i){
        if(a[i]<sum) add(0,i,sum-a[i],0),add(i,0,a[i]-sum,0);
        else if(a[i]>sum) add(i,n+1,a[i]-sum,0),add(n+1,i,sum-a[i],0);
        if(i==1) add(1,n,inf,1),add(n,1,0,-1),add(n,1,inf,1),add(1,n,0,-1);
        else add(i-1,i,inf,1),add(i,i-1,0,-1),add(i,i-1,inf,1),add(i-1,i,0,-1);
    }
    s=0,t=n+1;
    mcmf();
    cout<<cost<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
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

const int N=2e5+10;

int n,m,s;
struct egde{
    int to,w,nxt;
}e[N<<1];
int head[N],cnt=0;
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    head[u]=cnt;
}
struct node{
    int to,dis;
    bool operator < (const node &a)const{
        return dis>a.dis;
    }
};

int dis[N];
bool vis[N];
void dijkstra(int s){
    priority_queue<node> q;
    for(int i=1;i<=n;++i) dis[i]=0x3f3f3f3f,vis[i]=0;
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
                if(!vis[to]) q.push({to,dis[to]});
            }
        }
    }
}

signed main(){
    auto solve=[&](){
        read(n),read(m),read(s);
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            add(u,v,w);
        }
        dijkstra(s);
        for(int i=1;i<=n;++i){
            cout<<dis[i]<<' ';
        }
        cout<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
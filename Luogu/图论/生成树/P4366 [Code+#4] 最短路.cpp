#include<bits/stdc++.h>
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int Max=5e5+10,N=1e5+10,Ml=17;
struct edge{
    int to,nxt,w;
}e[N*Ml*4+Max];
struct node{
    int to,dis;
    bool operator < (const node& rhs) const{
        return !(dis<rhs.dis);
    }
};
int head[N*2],cnt=0,vis[2*N];
int dis[N*2];
int n,m,c;
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    head[u]=cnt;
}
int dijkstra(int s,int t){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    priority_queue<node> q;
    q.push({s,0});
    dis[s]=0;
    while(!q.empty()){
        int u=q.top().to,d=q.top().dis;
        q.pop();
        if(vis[u]) continue;
        if(u==t) return d;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            if(vis[to]) continue;
            if(e[i].w+dis[u]<dis[to]){
                dis[to]=e[i].w+dis[u];
                q.push({to,dis[to]});
            }
        }
    }
    return -1;
}
signed main(){
    auto solve=[&](){
        read(n),read(m),read(c);
        int p=log2(n);
        for(int i=1;i<=m;++i){
            int u,v,w;
            read(u),read(v),read(w);
            add(u,v,w);
        }
        for(int i=1;i<=n+(1<<p);++i){
            for(int j=0;j<=p;++j){
                int to=i^(1<<j);
                add(i,to,(1<<j)*c);
            }
        }
        int a,b;
        read(a),read(b);
        cout<<dijkstra(a,b)<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
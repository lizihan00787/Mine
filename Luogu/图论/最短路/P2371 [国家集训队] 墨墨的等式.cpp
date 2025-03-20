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

const int N=5e5+10,inf=1e18;

int n,l,r,x;

struct node{
    int to,dis;
    bool operator < (const node &a)const{
        return a.dis<dis;
    }
};
vector<PII> g[N];
int dis[N];
bool vis[N];

void dijkstra(){
    priority_queue<node> q;
    dis[0]=0;
    q.push({0,0});
    while(!q.empty()){
        int u=q.top().to;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto it:g[u]){
            int to=it.first;
            int w=it.second;
            if(dis[to]>dis[u]+w){
                dis[to]=dis[u]+w;
                q.push({to,dis[to]});
            }
        }
    }
}

inline void solve(){
    read(n,l,r,x);
    l--;
    for(int i=0;i<x;++i) dis[i]=inf;
    for(int i=1,y;i<n;++i){
        read(y);
        for(int i=0;i<x;++i) g[i].push_back(mk((i+y)%x,y));
    }
    dijkstra();
    int ans=0;
    for(int i=0;i<x;++i){
        if(l>=dis[i]) ans-=(l-dis[i])/x+1;
        if(r>=dis[i]) ans+=(r-dis[i])/x+1;
    }
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
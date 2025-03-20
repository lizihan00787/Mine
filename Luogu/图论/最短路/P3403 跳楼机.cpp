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

const int N=1e5+10,inf=(1ull<<63)-1;

int h,x,y,z;

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
    read(h,x,y,z);
    h--;
    for(int i=0;i<x;++i){
        g[i].push_back(mk((i+y)%x,y));
        g[i].push_back(mk((i+z)%x,z));
        dis[i]=inf;
    }
    dijkstra();
    int ans=0;
    for(int i=0;i<x;++i) if(h>=dis[i]) ans+=(h-dis[i])/x+1;
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
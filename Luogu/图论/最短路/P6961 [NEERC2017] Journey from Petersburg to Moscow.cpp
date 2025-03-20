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

const int N=3020;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,k;
ll w[N];
struct edge{
    int to,nxt;
    ll w;
}e[N<<1];
int head[N],cnt=0;
void add(int u,int v,ll w){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    head[u]=cnt;
}

struct node{
    int to;
    ll dis;
    bool operator < (const node &a)const{
        return dis>a.dis;
    }
};
ll dis[N];
bool vis[N];
ll dijkstra(ll x){
    priority_queue<node> q;
    for(int i=1;i<=n;++i) vis[i]=0,dis[i]=inf;
    q.push({1,0});
    dis[1]=0;
    while(!q.empty()){
        auto it=q.top();
        q.pop();
        int u=it.to;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int to=e[i].to;
            ll w=max(0ll,e[i].w-x);
            if(dis[to]>dis[u]+w){
                dis[to]=dis[u]+w;
                q.push({to,dis[to]});
            }
        }
    }
    return dis[n]+1ll*x*k;
}

signed main(){
    auto solve=[&](){
        read(n),read(m),read(k);
        for(int i=1;i<=m;++i){
            int u,v;
            read(u),read(v),read(w[i]);
            add(u,v,w[i]);
            add(v,u,w[i]);
        }
        w[m+1]=w[0]=1e9+7;
        sort(w+1,w+m+1);
        int nm=unique(w+1,w+m+1)-w-1;
        ll ans=dijkstra(0);
        int l=1,r=nm;
        while(l<=r){
            int mid=(l+r)>>1;
            ll num1=dijkstra(w[mid-1]),num2=dijkstra(w[mid]),num3=dijkstra(w[mid+1]);
            if(num1>=num2 && num2<=num3) {cout<<min(num2,ans)<<endl;return;}
            if(num1<=num2 && num2<=num3) r=mid-1;
            if(num1>=num2 && num2>=num3) l=mid+1;
        }
        cout<<ans<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
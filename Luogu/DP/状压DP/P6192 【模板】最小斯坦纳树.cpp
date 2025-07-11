#include<bits/stdc++.h>
#define endl '\n'
#define int  long long
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

const int N=120,inf=0x3f3f3f3f3f3f3f3f;

int n,m,k;
vector<PII> G[N];
int terminal[11];


inline void solve(){
    read(n,m,k);
    for(int i=1;i<=m;++i){
        int u,v,w;
        read(u,v,w);
        G[u].emplace_back(mk(v,w));
        G[v].emplace_back(mk(u,w));
    }
    vector<vector<int> > dp(1<<k,vector<int>(n+1,inf));
    for(int i=1;i<=k;++i) read(terminal[i]),dp[1<<(i-1)][terminal[i]]=0;
    for(int S=1;S<(1<<k);++S){
        for(int t=S;t;t=(t-1)&S)
            for(int u=1;u<=n;++u)
                dp[S][u]=min(dp[S][u],dp[t][u]+dp[S^t][u]);
        priority_queue<PII,vector<PII>,greater<PII> > q;
        vector<bool> vis(n+1,0);
        for(int i=1;i<=n;++i) if(dp[S][i]!=inf) q.push(mk(dp[S][i],i));
        while(!q.empty()){
            auto [d,u]=q.top();
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto [v,w]:G[u])
                if(dp[S][v]>dp[S][u]+w){
                    dp[S][v]=dp[S][u]+w;
                    q.push(mk(dp[S][v],v));
                }
        }
    }
    cout<<dp[(1<<k)-1][terminal[1]]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
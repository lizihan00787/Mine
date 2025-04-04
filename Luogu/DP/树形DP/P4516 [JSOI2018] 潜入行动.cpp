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

const int N=1e5+20;
const ll mod=1e9+7;

int n,k;
vector<int> G[N];
int dp[N][107][2][2],tmp[107][2][2];
int siz[N];

int add(int x,ll y){
    if(y>=mod) y%=mod;
    for(x+=y;x>=mod;x-=mod);
    return x;
}

void dfs(int u,int fa){
    siz[u]=dp[u][0][0][0]=dp[u][1][1][0]=1;
    for(auto v:G[u]){
        if(v==fa) continue;
        dfs(v,u);
        for(int i=0;i<=min(siz[u],k);++i){
            tmp[i][0][0]=dp[u][i][0][0]; dp[u][i][0][0]=0;
            tmp[i][0][1]=dp[u][i][0][1]; dp[u][i][0][1]=0;
            tmp[i][1][0]=dp[u][i][1][0]; dp[u][i][1][0]=0;
            tmp[i][1][1]=dp[u][i][1][1]; dp[u][i][1][1]=0;
        }
        for(int i=0;i<=min(siz[u],k);++i){
            for(int j=0;j<=min(siz[v],k-i);++j){
                dp[u][i+j][0][0]=add(dp[u][i+j][0][0],1ll*tmp[i][0][0]*dp[v][j][0][1]);

                dp[u][i+j][1][0]=add(dp[u][i+j][1][0],1ll*tmp[i][1][0]*(dp[v][j][0][0]+dp[v][j][0][1]));

                dp[u][i+j][0][1]=add(dp[u][i+j][0][1],1ll*tmp[i][0][1]*(dp[v][j][0][1]+dp[v][j][1][1]));
                dp[u][i+j][0][1]=add(dp[u][i+j][0][1],1ll*tmp[i][0][0]*dp[v][j][1][1]);

                dp[u][i+j][1][1]=add(dp[u][i+j][1][1],1ll*tmp[i][1][0]*(dp[v][j][1][0]+dp[v][j][1][1]));
                dp[u][i+j][1][1]=add(dp[u][i+j][1][1],1ll*tmp[i][1][1]*(1ll*dp[v][j][0][0]+dp[v][j][0][1]+1ll*dp[v][j][1][0]+dp[v][j][1][1]));
            }
        }
        siz[u]+=siz[v];
    }
}


inline void solve(){
    read(n,k);
    for(int i=1;i<n;++i){
        int u,v;
        read(u,v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,0);
    printf("%d\n",(int)((dp[1][k][0][1]+dp[1][k][1][1])%mod));
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
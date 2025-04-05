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

const int N=320,M=2e3+20;
const double inf=1e17+5;

int n,m,v,e;
int c[M][2];
double k[M];
int dis[M][M];
double dp[M][M][2];

inline void solve(){
    read(n,m,v,e);
    for(int i=1;i<=n;++i) read(c[i][0]);
    for(int i=1;i<=n;++i) read(c[i][1]);
    for(int i=1;i<=n;++i) cin>>k[i];
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=e;++i){
        int u,v,w;
        read(u,v,w);
        dis[u][v]=dis[v][u]=min(dis[u][v],w);
    }
    for(int k=1;k<=v;++k)
        for(int i=1;i<=v;++i)
            for(int j=1;j<=v;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=1;i<=v;++i) dis[i][i]=dis[i][0]=dis[0][i]=0;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=m;++j) dp[i][j][0]=dp[i][j][1]=inf;
    dp[1][0][0]=dp[1][1][1]=0;
    for(int i=2;i<=n;++i){
        dp[i][0][0]=dp[i-1][0][0]+dis[c[i-1][0]][c[i][0]];
        for(int j=1;j<=min(i,m);++j){
            //int C1 = c[i - 1][0], C2 = c[i - 1][1], C3 = c[i][0], C4 = c[i][1];
            //dp[i][j][0] = min(dp[i][j][0], min(dp[i - 1][j][0] + dis[C1][C3], dp[i - 1][j][1] + dis[C1][C3] * (1 - k[i - 1]) + dis[C2][C3] * k[i - 1]));
            //dp[i][j][1] = min(dp[i][j][1], min(dp[i - 1][j - 1][0] + dis[C1][C3] * (1 - k[i]) + dis[C1][C4] * k[i], dp[i - 1][j - 1][1] + dis[C2][C4] * k[i] * k[i - 1] + dis[C2][C3] * k[i - 1] * (1 - k[i]) + dis[C1][C4] * (1 - k[i - 1]) * k[i] + dis[C1][C3] * (1 - k[i - 1]) * (1 - k[i])));
            dp[i][j][0]=min(dp[i][j][0],min(dp[i-1][j][0]+dis[c[i-1][0]][c[i][0]],dp[i-1][j][1]+(1-k[i-1])*dis[c[i-1][0]][c[i][0]]+k[i-1]*dis[c[i-1][1]][c[i][0]]));
            dp[i][j][1]=min(dp[i][j][1],min(dp[i-1][j-1][0]+(1-k[i])*dis[c[i-1][0]][c[i][0]]+k[i]*dis[c[i-1][0]][c[i][1]],dp[i-1][j-1][1]+(1-k[i-1])*(1-k[i])*dis[c[i-1][0]][c[i][0]]+(1-k[i-1])*k[i]*dis[c[i-1][0]][c[i][1]]+(1-k[i])*k[i-1]*dis[c[i-1][1]][c[i][0]]+k[i-1]*k[i]*dis[c[i-1][1]][c[i][1]]));
        }
    }
    double ans=inf;
    for(int i=0;i<=m;++i) ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
    printf("%.2lf",ans);
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
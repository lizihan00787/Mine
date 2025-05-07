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

const int N=55;

int n,m,s;

int u[N],d[N];
int dp[N][10020];
int g[N][10020];

inline int F(int i,int j){
    return dp[i-1][j]+(m-d[i])*j;
}

inline void solve(){
    read(n,m,s);
    memset(dp,0x3f,sizeof(dp));
    memset(g,0x3f,sizeof(g));
    for(int i=1;i<=n;++i) read(u[i]);
    for(int i=1;i<=n;++i) read(d[i]);
    dp[0][0]=0;
    for(int i=1;i<=n;++i){
        for(int j=0;j<=s;++j){
            if(j!=0) g[i][j]=min(g[i][j-1],F(i,j));
            else g[i][j]=F(i,j);
        }
        for(int j=0;j<=s;++j){
            int lim=min(j+u[i],s);
            dp[i][j]=g[i][lim]+(j+u[i])*d[i];
        }
    }
    cout<<dp[n][0]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
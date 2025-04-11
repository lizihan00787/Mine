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

const int N=14;

int n,m,S;

int a[N][N],dp[N][N][10010];

inline void solve(){
    read(n,m);
    S=(1<<(m+1));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            read(a[i][j]);
    dp[0][m][0]=1;
    for(int i=1;i<=n;++i){
        for(int s=0;s<S;++s) dp[i][0][s<<1]=dp[i-1][m][s];
        for(int j=1;j<=m;++j)
            for(int s=0;s<S;++s){
                int p=(1<<j),q=(1<<(j-1));
                int x=s&p,y=s&q;
                if(!a[i][j]) if(!x && !y) dp[i][j][s]+=dp[i][j-1][s];
                else if(!x && y && a[i+1][j]) dp[i][j][s]+=dp[i][j-1][s^q^p]+dp[i][j-1][s];
                else if(x && y && a[i+1][j] && a[i][j+1]) dp[i][j][s]+=dp[i][j-1][s^q^p];
            }
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}
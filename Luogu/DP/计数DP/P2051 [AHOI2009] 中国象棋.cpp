#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
const int mod=9999973;
int dp[120][120][120];
int n,m;
int bal(int x){
    return (x*(x-1)/2)%mod;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        int ans=0;
        dp[0][0][0]=1;
        for(int i=1;i<=n;++i){
            for(int j=0;j<=m;++j){
                for(int k=0;k<=m-j;++k){
                    dp[i][j][k]=dp[i-1][j][k];
                    if(k>=1) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j+1][k-1]*(j+1))%mod;
                    if(j>=1) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j-1][k]*(m-j+1-k))%mod;
                    if(k>=1) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j][k-1]*j*(m-j-k+1))%mod;
                    if(j>=2) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j-2][k]*bal(m-j+2-k));
                    if(k>=2) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j+2][k-2]*bal(j+2));
                    dp[i][j][k]%=mod;
                }
            }
        }
        for(int i=0;i<=m;++i) for(int j=0;j<=m;++j) ans+=dp[n][i][j],ans%=mod;
        cout<<ans<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
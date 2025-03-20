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
int dp[1020][1020],sum=0;
int n,k;
const int mod=1e4;
signed main(){
    auto solve=[&](){
        read(n),read(k);
        dp[1][0]=1;
        for(int i=2;i<=n;++i){
            sum=0;
            for(int j=0;j<=k;++j){
                sum+=dp[i-1][j],sum%=mod;
                dp[i][j]=sum;
                if(j-i+1>=0) sum-=dp[i-1][j-i+1],sum%=mod,sum+=mod,sum%=mod;
            }
        }
        cout<<dp[n][k]%mod;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
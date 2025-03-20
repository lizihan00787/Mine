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
char a[1020];
int dp[1020];
bool g[1020][1020];
signed main(){
    auto solve=[&](){
        cin>>a+1;
        int n=strlen(a+1);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i){
            g[i][i]=1;
            g[i-1][i]=(a[i-1]==a[i]);
        }
        for(int j=2;j<=n;++j){
            for(int i=1;i<j-1;++i){
                if(a[i]==a[j]) g[i][j]=g[i+1][j-1];
                else g[i][j]=0;
            }
        }
        for(int i=1;i<=n;++i){
            dp[i]=dp[i-1]+1;
            for(int j=1;j<i;++j){
                if(g[j][i]) dp[i]=min(dp[i],dp[j-1]+1);
            }
        }
        cout<<dp[n]<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    read(T);
    while(T--) solve();
    return 0;
}
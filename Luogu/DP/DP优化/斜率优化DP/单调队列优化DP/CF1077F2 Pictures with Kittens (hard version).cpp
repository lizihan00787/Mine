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
int n,m,k;
int a[5020];
int dp[5020][5020];
int q[5020];
int h,t;
signed main(){
    auto solve=[&](){
        read(n),read(m),read(k);
        for(int i=1;i<=n;++i) read(a[i]);
        memset(dp,0xcf,sizeof(dp));
        if(n/m>k){
            puts("-1");
            return;
        }
        dp[0][0]=0;
        for(int j=1;j<=k;++j){
            h=1,t=0;
            q[++t]=0;
            for(int i=1;i<=n;++i){
                while(h<=t && i-q[h]>m) h++;
                dp[i][j]=dp[q[h]][j-1]+a[i];
                while(h<=t && dp[i][j-1]>=dp[q[t]][j-1]) t--;
                q[++t]=i;
            }
        }
        int maxx=0;
        for(int i=n-m+1;i<=n;++i) maxx=max(maxx,dp[i][k]);
        cout<<maxx<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
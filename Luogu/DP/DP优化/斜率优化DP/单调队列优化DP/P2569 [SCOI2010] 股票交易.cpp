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
int n,p,w;
int dp[2020][2020];
int q[2020];
int h,t;
signed main(){
    auto solve=[&](){
        read(n),read(p),read(w);
        memset(dp,-0x3f3f3f3f3f3f3f3f,sizeof(dp));
        for(int i=1;i<=n;++i){
            int ap,bp,aj,bj;
            read(ap),read(bp),read(aj),read(bj);
            for(int j=0;j<=aj;++j) dp[i][j]=-j*ap;
            for(int j=0;j<=p;++j) dp[i][j]=max(dp[i][j],dp[i-1][j]);
            if(i<=w) continue;
            h=1,t=0;
            for(int j=0;j<=p;++j){
                while(h<=t && j-q[h]>aj) h++;
                while(h<=t && dp[i-w-1][q[t]]+q[t]*ap<=dp[i-w-1][j]+j*ap) t--;
                q[++t]=j;
                if(h<=t) dp[i][j]=max(dp[i][j],dp[i-w-1][q[h]]+q[h]*ap-j*ap);
            }
            h=1,t=0;
            for(int j=p;j>=0;--j){
                while(h<=t && j-q[h]<-bj) h++;
                while(h<=t && dp[i-w-1][q[t]]+q[t]*bp<=dp[i-w-1][j]+j*bp) t--;
                q[++t]=j;
                if(h<=t) dp[i][j]=max(dp[i][j],dp[i-w-1][q[h]]+q[h]*bp-j*bp);
            }
        }
        int ans=0;
        for(int i=0;i<=p;++i) ans=max(ans,dp[n][i]);
        cout<<ans<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
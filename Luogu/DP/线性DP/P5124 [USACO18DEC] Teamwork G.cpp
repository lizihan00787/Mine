#include<bits/stdc++.h>
#define int long long
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
int n,k;
int a[10200];
int dp[10200];
signed main(){
    auto solve=[&](){
        read(n),read(k);
        for(int i=1;i<=n;++i) read(a[i]);
        int len=1;
        for(int i=1;i<=n;++i){
            int maxx=-1;
            for(int j=i;j>=max(1ll,i-k+1);--j){
                maxx=max(maxx,a[j]);
                dp[i]=max(dp[i],dp[j-1]+maxx*(i-j+1));
            }
        }
        cout<<dp[n]<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
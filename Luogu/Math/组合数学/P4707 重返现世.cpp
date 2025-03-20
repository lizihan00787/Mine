#include<bits/stdc++.h>
#define int long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define mod 998244353
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
int dp[2][10010][14];
int p[1010];
int n,m,k;
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a,res%=mod;
		a=a*a,a%=mod;
		b>>=1;
	}
	return res;
}
int inv(int x){
	return qpow(x,mod-2);
}
signed main(){
    auto solve=[&](){
        read(n),read(k),read(m);
        k=n-k+1;
        for(int i=1;i<=n;++i) read(p[i]),dp[i&1][0][0]=1;
        for(int i=1;i<=n;++i){ 
        	for(int j=0;j<=p[i]-1;++j) for(int l=1;l<=10;++l)dp[i&1][j][l]=dp[(i&1)^1][j][l];
        	for(int j=p[i];j<=m;++j){
        		for(int l=1;l<=10;++l){
        			dp[i&1][j][l]=dp[(i&1)^1][j][l]+dp[(i&1)^1][j-p[i]][l-1]-dp[(i&1)^1][j-p[i]][l];
        			dp[i&1][j][l]=(dp[i&1][j][l]%mod+mod)%mod;
				}
			}
		}
		int ans=0;
		for(int j=1;j<=m;++j){
			ans+=m*dp[n&1][j][k]%mod*inv(j)%mod;
			ans=(ans%mod+mod)%mod;
		}
		cout<<ans<<endl;
    };
    io();
    //read(T);
    while(T--) solve();
    return 0;
}

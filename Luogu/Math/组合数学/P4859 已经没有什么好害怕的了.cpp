#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
using namespace std;
int T=1;
int n,k;
int a[2020],b[2020];
int jc[2020];
int dp[2020][2020],ans;
const int mod=1e9+9;
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=a*res,res%=mod;
		a=a*a,a%=mod;
		b>>=1;
	}
	return res;
}
int inv(int x){
	return qpow(x,mod-2)%mod;
}
int ml(int n,int m){
	if(n<m) return 0;
	return jc[n]%mod*inv(jc[n-m])%mod*inv(jc[m])%mod;
}
signed main(){
	auto solve=[&](){
		read(n),read(k);
		if((n+k)&1){
			cout<<0<<endl;
			return ;
		}
		k=(n+k)/2;
		jc[0]=jc[1]=1;
		for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i,jc[i]%=mod;
		for(int i=1;i<=n;++i) read(a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n;++i) read(b[i]),dp[i][0]=1;
		sort(b+1,b+n+1);
		dp[0][0]=1;
		for(int i=1;i<=n;++i){
			int cnt=0;
			for(int j=1;j<=n;++j) if(a[i]>b[j]) cnt++;
			for(int j=0;j<=i;++j){
				dp[i][j]=dp[i-1][j]+dp[i-1][j-1]*(cnt-j+1);
				dp[i][j]%=mod;
			}
		}
		for(int i=k;i<=n;++i){
			if((i-k)%2==0) ans=(ans+ml(i,k)%mod*jc[n-i]%mod*dp[n][i]%mod+mod)%mod;
			else ans=(ans-ml(i,k)%mod*jc[n-i]%mod*dp[n][i]%mod+mod)%mod;
		}
		cout<<(ans%mod+mod)%mod<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



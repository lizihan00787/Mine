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
const int mod=1e9+7;
int jc[2000010],infac[2000010];
int qpow(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1) res=a*res%p;
		a=a*a%p;
		b>>=1;
	}
	return res%p;
}
int ml(int n,int m){
	return jc[n]*infac[m]%mod*infac[n-m]%mod;
}
signed main(){
	auto solve=[&](){
		read(n),read(k);
		jc[0]=infac[0]=1;
		for(int i=1;i<=1000010;++i) jc[i]=jc[i-1]*i,jc[i]%=mod,infac[i]=qpow(jc[i],mod-2,mod)%mod;
		int ans=0;
		int p=ml(n,k);
		n-=k;
		for(int i=n; i>=0; i--){
			if(i%2==0){
				ans=(ans+ml(n,i)%mod*(qpow(2ll,qpow(2ll,n-i,mod-1),mod)-1)%mod)%mod;
			}
			else{
				ans=(ans-ml(n,i)%mod*(qpow(2ll,qpow(2ll,n-i,mod-1),mod)-1)%mod+mod)%mod;
			}
        	ans%=mod;
    	}
		cout<<ans*p%mod<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



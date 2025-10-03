#include<bits/stdc++.h>
//#define int long long
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
int n,m;
int w[120],z[120];
long long dp[100010];
signed main(){
	auto solve=[&](){
		read(n);
		int u,v,c=0;
		long long res=0x3f3f3f3f3f3f3f3f;
		memset(dp,0x3f,sizeof(dp));
		for(int i=0;i<n;++i){
			read(u),read(v),read(z[i]);
			if(u<v) w[i]=(u+v+1)/2-u;
			c+=z[i];
		}
		dp[0]=0;
		for(int i=0;i<n;++i){
			for(int j=c;j>=z[i];--j){
				dp[j]=min(dp[j-z[i]]+w[i],dp[j]);
			}
		}
		for(int i=(c+1)/2;i<=c;++i) res=min(res,dp[i]);
		cout<<res<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



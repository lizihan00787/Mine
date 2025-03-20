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
int n,Q;
int a[100010],k[100010];
int dp[100010];
int q[100010];
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i) read(a[i]);
		read(Q);
		for(int i=1;i<=Q;++i) read(k[i]);
		for(int i=1;i<=Q;++i){
			for(int j=1;j<=n;++j) q[j]=0;
			for(int j=1;j<=n+1;++j) dp[j]=0x3f3f3f3f3f3f3f3f;
			int len=k[i];
			int ans=0x3f3f3f3f3f3f3f3f;
			int h=1,t=0;
			for(int j=1;j<=n;++j){
				while(h<=t && dp[q[t]]>dp[j]) t--;
				q[++t]=j;
				while(h<=t && q[h]+len<j) h++;
				dp[j+1]=min(dp[j+1],dp[j+1]+(a[q[h]]<=a[j+1]?1:0)+dp[q[h]]);
				if(j+1>=n) ans=min(ans,dp[j+1]);
			}
			cout<<ans<<endl;
		}
		return;
	};
	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


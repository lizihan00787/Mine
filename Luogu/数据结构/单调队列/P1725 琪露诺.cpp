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
int n,l,r;
int a[200010];
int dp[200010];
int q[200010];
signed main(){
	auto solve=[&](){
		memset(dp,-0x3f,sizeof(dp)); 
		read(n),read(l),read(r);
		dp[0]=0;
		for(int i=0;i<=n;++i) read(a[i]);
		int tail=1,head=1,ans=-0x3f3f3f3f3f3f3f3f;
		for(int i=l;i<=n;++i){
			int y=i-l;
			while(head<=tail && dp[y]>=dp[q[tail]]) tail--;
			q[++tail]=y;
			while(head<=tail && q[head]+r<i) head++;
			dp[i]=dp[q[head]]+a[i]; 
			if(i+r>n) ans=max(ans,dp[i]);
		}
		cout<<ans<<endl;
		return;
	};
	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


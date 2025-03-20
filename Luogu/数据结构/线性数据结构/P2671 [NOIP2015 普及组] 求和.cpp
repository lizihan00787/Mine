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
const int mod=10007;
int n,m;
int num[100010];
int col[100010];
int sum[4][100010][2];
signed main(){
	auto solve=[&](){
		read(n),read(m);
		for(int i=1;i<=n;++i) read(num[i]);
		for(int i=1;i<=n;++i) read(col[i]);
		int ans=0;
		for(int i=1;i<=n;++i){
			int cx=col[i],x=num[i];
			ans=(ans%mod+sum[0][col[i]][i&1]%mod+i*sum[1][col[i]][i&1]%mod+i*x*sum[2][col[i]][i&1]%mod+x*sum[3][col[i]][i&1]%mod+mod)%mod; 
			sum[0][col[i]][i&1]=(sum[0][col[i]][i&1]%mod+(i*num[i])%mod+mod)%mod;
			sum[1][col[i]][i&1]=(sum[1][col[i]][i&1]%mod+num[i]%mod+mod)%mod;
			sum[2][col[i]][i&1]=(sum[2][col[i]][i&1]%mod+1+mod)%mod;
			sum[3][col[i]][i&1]=(sum[3][col[i]][i&1]%mod+i+mod)%mod;
		}
		cout<<ans%mod<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



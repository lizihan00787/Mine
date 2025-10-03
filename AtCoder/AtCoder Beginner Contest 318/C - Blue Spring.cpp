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
int n,d,p;
int a[200010];
int sum[200010];
signed main(){
	auto solve=[&](){
		cin>>n>>d>>p;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}
		sort(a+1,a+n+1,greater<int>());
		for(int i=n;i>=1;--i){
			sum[i]=sum[i+1]+a[i];
		}
		int ans=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;++i){
			if(i%d==0){
				ans=min(ans,sum[i+1]+(i/d)*p);
			}
		}
		ans=min(ans,sum[1]);
		int cs=n/d+1;
		ans=min(ans,cs*p);
		cout<<ans<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



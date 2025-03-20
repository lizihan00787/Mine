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
int n;
int a[300010];
int b[300010];
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i) read(a[i]);
		for(int i=1;i<=n;++i) read(b[i]);
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		int sum1=0,sum2=0;
		for(int i=1;i<=n;++i) sum1+=a[1]+b[i];
		for(int i=1;i<=n;++i) sum2+=a[i]+b[1];
		cout<<min(sum1,sum2)<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}



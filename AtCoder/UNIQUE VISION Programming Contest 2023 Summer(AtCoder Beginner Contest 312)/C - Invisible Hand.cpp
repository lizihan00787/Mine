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
int n,m;
int a[200010];
int b[200010];
signed main(){
	auto check=[&](int x){
		int sel=upper_bound(a+1,a+n+1,x)-a-1;
		int bou=m-(lower_bound(b+1,b+m+1,x)-b)+1;
		if(sel>=bou) return 0;
		else return 1;
	};
	auto solve=[&](){
		read(n),read(m);
		for(int i=1;i<=n;++i) read(a[i]);
		for(int i=1;i<=m;++i) read(b[i]);
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		int l=0,r=1e9+100,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)) l=mid+1;
			else r=mid-1,ans=mid;
		}
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



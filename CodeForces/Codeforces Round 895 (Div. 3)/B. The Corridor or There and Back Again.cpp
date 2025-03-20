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
int d[120],s[120];
map<int,int> q;
signed main(){
	auto check=[&](int k){
		for(int i=1;i<=k;++i){
			for(int j=1;j<=n;++j){
				int x=d[j];
				int y=s[j];
				if(x>k) continue;
				int cz=2*(k-x);
				if(cz>=y){
					return 0;
				}
			}
		}
		return 1;
	};
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i){
			read(d[i]),read(s[i]);
		}
		int l=1,r=1e9,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		cout<<ans<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}



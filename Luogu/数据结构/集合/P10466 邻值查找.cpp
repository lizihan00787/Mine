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
map<int,int> p;
int n;
int a[100010];
set<PII> q;
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i) read(a[i]);
		q.insert(mk(a[1],1));
		for(int i=2;i<=n;++i){
			q.insert(mk(a[i],i));
			auto t=q.find(mk(a[i],i));
			int ans=0x3f3f3f3f3f3f3f3f,ansk=0;
			if(++t!=q.end()) ans=t->first-a[i],ansk=t->second;
			--t;
			if(t--!=q.begin() && ans>=a[i]-t->first) ans=a[i]-t->first,ansk=t->second;
			cout<<ans<<" "<<ansk<<endl;
		}
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



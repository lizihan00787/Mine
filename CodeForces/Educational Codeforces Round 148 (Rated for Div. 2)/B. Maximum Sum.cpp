#include<bits/stdc++.h>
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
int T=1;
const int Max=2e5+10;
int a[Max];
int n,k;
signed main(){
	auto solve=[&](){
		cin>>n>>k;
		vector<int> pre(n+2);
		vector<int> fix(n+2);
		for(int i=1;i<=n;++i) cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<=n;++i) pre[i]=pre[i-1]+a[i];
		int ans=0;
		for(int i=0;i<=k;++i){
			int now=pre[n-(k-i)]-pre[2*i];
			ans=max(ans,now);
		}
		cout<<ans<<endl;
	};
	io();
	cin>>T;
	while(T--) solve();
	return 0;
}



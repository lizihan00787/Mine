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
int n;
int a[200010];
int sum[200010],sum2[200010];
int Q;
signed main(){
	auto solve=[&](){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=n;++i) sum[i]=a[i]-a[i-1];
		cin>>Q;
		for(int i=1;i<=n;i+=2){
			sum2[i]=sum[i]+sum2[i-2];
			sum2[i-1]=sum2[i-2];
			sum2[i+1]=sum2[i];
		}
		for(int i=1;i<=Q;++i){
			int l,r;
			cin>>l>>r;
			int x=lower_bound(a+1,a+n+1,l)-a;
			int y=lower_bound(a+1,a+n+1,r)-a-1;
			int res=0;
			if(y<x){
	            if(x%2==1) res+=r-l;
	        }
	        else{
	            res+=sum2[y]-sum2[x];
	            if(x%2==1) res+=a[x]-l;
	            if(y%2==0) res+=r-a[y];
	        }
			cout<<res<<endl;
		}
	};
	io();

	while(T--) solve();
	return 0;
}



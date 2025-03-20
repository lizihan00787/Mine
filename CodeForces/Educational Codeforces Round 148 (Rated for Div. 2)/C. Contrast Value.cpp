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
int a[300010];
signed main(){
	auto solve=[&](){
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}
		int now=0,ans=1;
		for(int i=2;i<=n;++i){
			if(a[i]>a[i-1]){
				if(now==1) continue;
				else{
					now=1;
					ans++;
				}
			}
			if(a[i]<a[i-1]){
				if(now==-1) continue;
				else{
					now=-1;
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	};
	io();
	cin>>T;
	while(T--) solve();
	return 0;
}



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
int n,k;
signed main(){
	auto solve=[&](){
		cin>>n>>k;
		int ans=(n+k-1)/k;
        if(k>1 && n%k!=1) ans+=1;
        cout<<ans<<endl;
	};
	io();
	cin>>T;
	while(T--) solve();
	return 0;
}



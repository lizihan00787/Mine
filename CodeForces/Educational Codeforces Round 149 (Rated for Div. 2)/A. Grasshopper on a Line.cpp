#include<bits/stdc++.h>
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
int x,k;
signed main(){
	auto solve=[&](){
		cin>>x>>k;
		if(x%k!=0 || k>x){
			cout<<1<<endl<<x<<endl;
		}
		else if(x%k==0){
			cout<<2<<endl;
			cout<<x-1<<' '<<1<<endl;
		}
	};
	io();
	cin>>T;
	while(T--) solve();
	return 0;
}



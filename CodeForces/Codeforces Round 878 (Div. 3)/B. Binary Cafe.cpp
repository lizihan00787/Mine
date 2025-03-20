#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
int n,k;
signed main(){
	auto solve=[&](){
		cin>>n>>k;
		if(k>=30) cout<<n+1<<endl;
		else cout<<min(n+1,(int)(1<<k))<<endl;
	};
	io();
	cin>>T;
	while(T--) solve();
	return 0;
}



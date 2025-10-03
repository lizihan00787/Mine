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
#define mk(a,b) make(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
int n,a,b;
signed main(){
	auto solve=[&](){
		cin>>n>>a>>b;
		int x;
		for(int i=1;i<=n;++i){
			cin>>x;
			if(x==a+b){
				cout<<i<<endl;
				return;
			}
		}
	};
	io();
	
	while(T--) solve();
	return 0;
}


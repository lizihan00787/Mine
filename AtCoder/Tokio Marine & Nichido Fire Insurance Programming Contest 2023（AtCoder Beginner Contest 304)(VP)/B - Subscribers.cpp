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
signed main(){
	auto solve=[&](){
		string s;
		cin>>s;
		if(s.size()<=3) cout<<s<<'\n';
		else cout<<s.substr(0,3)<<string(s.size()-3,'0')<<'\n';
	};
	io();

	while(T--) solve();
	return 0;
}



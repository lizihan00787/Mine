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
int n;
struct node{
	int x;
	string name;
}a[120];
signed main(){
	auto cmp=[&](node a,node b){
		return a.x<b.x;
	};
	auto solve=[&](){
		cin>>n;
		int minn=0x3f3f3f3f,mink=0;
		for(int i=1;i<=n;++i){
			cin>>a[i].name>>a[i].x;
			if(a[i].x<minn) minn=a[i].x,mink=i;
		}
		for(int i=mink;i<=n;++i){
			cout<<a[i].name<<endl;
		}
		for(int i=1;i<mink;++i){
			cout<<a[i].name<<endl;
		}
	};
	io();

	while(T--) solve();
	return 0;
}



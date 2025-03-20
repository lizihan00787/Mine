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
int n;
char s[120];
int a1=0,a2=0;
signed main(){
	auto solve=[&](){
		cin>>n;
		cin>>s+1;
		for(int i=1;i<=n;++i){
			if(s[i]=='T') a1++;
			else if(s[i]=='A') a2++;
		}
		if(a1==a2){
			if(s[n]=='A') cout<<'T'<<endl;
			else cout<<'A'<<endl;
		}
		else if(a1>a2) cout<<'T'<<endl;
		else cout<<'A'<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}



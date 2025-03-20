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
char a[120],b[120];
int n;
signed main(){
	auto solve=[&](){
		cin>>n;
		cin>>a+1;
		cin>>b+1;
		for(int i=1;i<=n;++i){
			if(a[i]!=b[i]){
				if((a[i]=='1' && b[i]=='l') || (a[i]=='0' && b[i]=='o')) continue;
				else if((a[i]=='l' && b[i]=='1') || (a[i]=='o' && b[i]=='0')) continue;
				else{
					cout<<"No"<<endl;
					return;
				}
			}
		}
		cout<<"Yes"<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}



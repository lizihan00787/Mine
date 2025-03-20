#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
//#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
int n;
char a[120];
vector<char> ans;
signed main(){
	auto solve=[&](){
		cin>>n;
		cin>>a+1;
		ans.clear();
		int k=1;
		char w;
		while(k<=n){
			w=a[k];
			ans.push_back(a[k]); 
			for(int j=k+1;j<=n;++j){
				if(a[j]==w){
					k=j;
					break;
				}
			}
			k+=1;
		};
		for(auto it:ans){
			cout<<it;
		}
		cout<<endl;
		return;
	};
	cin>>T;
	while(T--) solve();
	return 0;
}



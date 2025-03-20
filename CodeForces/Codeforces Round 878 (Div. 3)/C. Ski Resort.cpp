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
int n,k,p;
int a[200010];
int sum[200010];
map<int,int> dat,date;
signed main(){
	auto solve=[&](){
		dat.clear();
		date.clear();
		cin>>n>>k>>p;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}
		for(int i=1;i<=n;++i){
			sum[i]=sum[i-1]+(a[i]<=p?1:0);
			if(a[i]>p) sum[i]=0;
			if(sum[i]==0){
				dat[sum[i-1]]++;
			}
		}
		if(sum[n]!=0){
			dat[sum[n]]++;
		}
		for(auto it:dat){
			if(it.first>=k) date[it.first]=it.second;
		}
		int ans=0;
		for(auto it:date){
			int num=it.second;
			int sum=it.first;
			ans+=(sum-k+1+1)*(sum-k+1)/2*num;
		}
		cout<<ans<<endl;
	};
	io();
	cin>>T; 
	while(T--) solve();
	return 0;
}



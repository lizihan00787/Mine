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
int n,m;
int a[70][70];
map<PII,bool> q;
signed main(){
	auto solve=[&](){
		cin>>m>>n;
		q.clear();
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<m;++j){
				q[mk(a[i][j],a[i][j+1])]=1;
				q[mk(a[i][j+1],a[i][j])]=1;
			}
		}
		int ans=0;
		for(int i=1;i<=m;++i){
			for(int j=i+1;j<=m;++j){
				if(!q[mk(i,j)] && i!=j) ans++;
			}
		}
		cout<<ans<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}



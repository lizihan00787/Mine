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
char s[12][12];
int a[12][12];
map<int,bool> q;
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>s[i][j];
			}
		}
		if(m==1){
			cout<<"Yes"<<endl;
			return;
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(i!=j){
					int sum=0;
					for(int k=1;k<=m;++k){
						if(s[i][k]!=s[j][k]){
							sum++;
						}
					}
					a[i][j]=a[j][i]=sum;
				}
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(a[i][j]==1 || a[j][i]==1){
					q[i]=q[j]=1;
				}
			}
		}
		for(int i=1;i<=n;++i){
			if(q[i]==0){
				cout<<"No"<<endl;
				return;
			}
		}
		cout<<"Yes"<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}



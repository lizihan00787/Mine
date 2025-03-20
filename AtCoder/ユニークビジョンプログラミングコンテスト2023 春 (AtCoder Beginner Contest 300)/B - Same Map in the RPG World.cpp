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
int n,m;
char a[150][150];
char b[40][40];
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		for(int i=n+1;i<=n+n;++i){
			for(int j=m+1;j<=m+m;++j){
				cin>>a[i][j];
				a[i-n][j]=a[i][j];
				a[i+n][j]=a[i][j];
				a[i][j+m]=a[i][j];
				a[i][j-m]=a[i][j];
				a[i-n][j-m]=a[i][j];
				a[i-n][j+m]=a[i][j];
				a[i+n][j-m]=a[i][j];
				a[i+n][j+m]=a[i][j];
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>b[i][j];
			}
		}
		for(int i=1;i<=3*n;++i){
			for(int j=1;j<=3*m;++j){
				if(a[i][j]==b[1][1]){
					bool p=1;
					for(int ii=1;ii<=n;++ii){
						for(int jj=1;jj<=m;++jj){
							if(a[i+ii-1][j+jj-1]!=b[ii][jj]){
								p=0;
								break;
							}
							else{
								continue;
							}
						}
						if(p==0){
							break;
						}
					}
					if(p==1){
						cout<<"Yes"<<endl;
						return;
					}
				}
			}
		}
		cout<<"No"<<endl;
		return;
	};
	io();

	while(T--) solve();
	return 0;
}



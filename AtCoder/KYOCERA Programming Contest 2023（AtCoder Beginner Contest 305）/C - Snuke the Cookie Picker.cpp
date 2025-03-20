#include<bits/stdc++.h>
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
int n,m;
char a[520][520];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		int x,y;
		bool p=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(a[i][j]=='.'){
					int cnt=0;
					for(int k=0;k<=3;++k){
						int nx=i+dx[k];
						int ny=j+dy[k];
						if(a[nx][ny]=='#'){
							cnt++;
						}
					}
					if(cnt>=2){
						cout<<i<<' '<<j<<endl;
						break;
					}
				}
			}
		}
	};
	io();

	while(T--) solve();
	return 0;
}



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
int b[120][120];
int c1[120][120];
int c2[120][120];
int c3[120][120];
int c4[120][120];
signed main(){
	auto solve=[&](){
		cin>>n;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				int x;
				cin>>x;
				if(x==1) c1[i][j]=c2[j][n+1-i]=c3[n+1-i][n+1-j]=c4[n+1-j][i]=1;
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				cin>>b[i][j];
			}
		}
		bool flag1=1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(c1[i][j]==1){
					if(b[i][j]==1) continue;	
					else{
						flag1=0;
					}
				}
			}
		}
		bool flag2=1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(c2[i][j]==1){
					if(b[i][j]==1) continue;	
					else{
						flag2=0;
					}
				}
			}
		}
		bool flag3=1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(c3[i][j]==1){
					if(b[i][j]==1) continue;	
					else{
						flag3=0;
					}
				}
			}
		}
		bool flag4=1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(c4[i][j]==1){
					if(b[i][j]==1) continue;	
					else{
						flag4=0;
					}
				}
			}
		}
		cout<<(flag1==0 && flag2==0 && flag3==0 && flag4==0?"No":"Yes")<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}


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
char mapp[120][120];
int xx[8]={0,1,0,-1,1,1,-1,-1};
int yy[8]={1,0,-1,0,1,-1,1,-1};
char a[6]={' ','s','n','u','k','e'};
stack<PII> q;
void print(){
	vector<PII> p;
	while(!q.empty()){
		p.push_back(q.top());
		q.pop();
	}
	for(int i=p.size()-1;i>=0;--i){
		cout<<p[i].first<<' '<<p[i].second<<endl;
	}
	return;
}
void dfs(int x,int y,int s,int f){
	if(s==5){
		print();
		exit(0);
	}
	int nx=x+xx[f];
	int ny=y+yy[f];
	if(nx>=1 && nx<=n && ny>=1 && ny<=m && mapp[nx][ny]==a[s+1]){
		q.push({nx,ny});
		dfs(nx,ny,s+1,f);
		q.pop();
	}
}
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>mapp[i][j];
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(mapp[i][j]=='s'){
					for(int k=0;k<=7;++k){
						while(!q.empty()){
							q.pop();
						}
						q.push({i,j});
						dfs(i,j,1,k);
					}
					
				}
			}
		}
	};
	io();

	while(T--) solve();
	return 0;
}



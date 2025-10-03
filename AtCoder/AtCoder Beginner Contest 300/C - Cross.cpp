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
const int xx[4]={1,1,-1,-1};
const int yy[4]={1,-1,-1,1};
int qx=0,qy=0;
int sumz=0,sumy=0;
bool p=0;
map<int,int> q;
void dfs2(int x,int y,int ss){
	int nx=x+1,ny=y-1;
	if(mapp[nx][ny]=='#'){
		dfs2(nx,ny,ss+1);
	}
	else{
		int sumy=ss;
		if(sumz!=sumy){
			return;
		}
		else{
			p=1;
			return;
		}
	}
}
void dfs1(int x,int y,int s){
	int nx=x+1,ny=y+1;
	if(mapp[nx][ny]=='#'){
		dfs1(nx,ny,s+1);
	}
	else{
		sumz=s;
		dfs2(qx,y,1);
		return;
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
				if(mapp[i][j]=='#'){
					qx=i,qy=j;
					p=0;
					sumz=0,sumy=0;
					dfs1(i,j,1);
					if(p==1){
						q[(long long)(sumz/2)]++;
					}
					else{
						continue;
					}
				}
			}
		}
		for(int i=1;i<=min(n,m);++i){
			cout<<q[i]<<' ';
		}
		cout<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}
/*
5 9
....#...#
.....#.#.
......#..
.....#.#.
....#...#
*/


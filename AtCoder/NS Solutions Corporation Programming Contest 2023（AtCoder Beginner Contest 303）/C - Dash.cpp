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
int n,m,h,k;
map<PII,int> q;
char a[200010];
signed main(){
	auto solve=[&](){
		cin>>n>>m>>h>>k;
		cin>>a+1;
		int x,y;
		for(int i=1;i<=m;++i){
			cin>>x>>y;
			q[mk(x,y)]=k;
		}
		int xx=0,yy=0;
		for(int i=1;i<=n;++i){
			if(a[i]=='R') xx+=1,h-=1;
			else if(a[i]=='L') xx-=1,h-=1;
			else if(a[i]=='U') yy+=1,h-=1;
			else if(a[i]=='D') yy-=1,h-=1;
			if(h<0){
				cout<<"No"<<endl;
				return;
			}
			else if(q[mk(xx,yy)]>0 && h<k){
				h=k;
				q[mk(xx,yy)]=0;
			}
		}
		cout<<"Yes"<<endl;
		return;
	};
	io();

	while(T--) solve();
	return 0;
}



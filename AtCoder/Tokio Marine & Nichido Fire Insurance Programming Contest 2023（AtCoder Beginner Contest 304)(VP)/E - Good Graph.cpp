#include<bits/stdc++.h>
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
int n,m,k,Q;
int u,v;
int fa[200010];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void unionn(int a,int b){
	int x=find(a);
	int y=find(b);
	if(x!=y) fa[x]=y;
}
set<PII> q;
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		for(int i=1;i<=n;++i) fa[i]=i;
		for(int i=1;i<=m;++i){
			cin>>u>>v;
			unionn(u,v);
		}
		cin>>k;
		for(int i=1;i<=k;++i){
			cin>>u>>v;
			int a=find(u),b=find(v);
			q.emplace(mk(a,b));
			q.emplace(mk(b,a));
		}
		cin>>Q;
		for(int i=1;i<=Q;++i){
			cin>>u>>v;
			if(q.count(mk(find(u),find(v)))) cout<<"No"<<endl;
			else cout<<"Yes"<<endl;
		}
	};
	io();

	while(T--) solve();
	return 0;
}



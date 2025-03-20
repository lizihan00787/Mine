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
int fa[2010];
int x,y;
int n,d;
struct node{
	int x,y;
}a[2010];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void unionn(int a,int b){
	int x=find(a);
	int y=find(b);
	if(x!=y) fa[x]=y;
}
signed main(){
	auto solve=[&](){
		cin>>n>>d;
		for(int i=1;i<=n;++i){
			fa[i]=i;
		}
		for(int i=1;i<=n;++i){
			cin>>a[i].x>>a[i].y;
		}
		for(int i=1;i<=n;++i){
			for(int j=i+1;j<=n;++j){
				if((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y)<=d*d){
					unionn(i,j);
				}
			}
		}
		for(int i=1;i<=n;++i){
			if(find(i)==find(1)) cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	};
	io();

	while(T--) solve();
	return 0;
}



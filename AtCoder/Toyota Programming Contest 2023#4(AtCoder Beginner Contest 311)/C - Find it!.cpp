#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
struct edge{
	int to,nxt;
}e[200010<<1];
int head[200010],cnt=0;
int n;
void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
	return;
}
bool vis[200010];
int a[200010];
deque<int> q;
deque<int> ans;
void print(int no){
	bool p=0;
	while(!q.empty()){
		if(q.front()==no) p=1;
		if(p==1) ans.push_back(q.front());
		q.pop_front();
	}
	cout<<ans.size()<<endl;
	while(1){
		if(ans.front()==a[ans.back()]) break;
		ans.push_back(ans.front());
		ans.pop_front();
	}
	while(!ans.empty()){
		cout<<ans.front()<<' ';ans.pop_front();
	}
	exit(0);
}
void dfs(int qd,int u){
	vis[u]=1;
	q.push_back(u);
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(vis[to]){
			print(to);
		}
		if(!vis[to]){
			dfs(qd,to);
		}
	}
}
signed main(){
	auto solve=[&](){
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			add(i,a[i]);
		}
		for(int i=1;i<=n;++i){
			if(!vis[i]){
				dfs(i,i);
			}
		}
		return;
	};
	while(T--) solve();
	return 0;
}


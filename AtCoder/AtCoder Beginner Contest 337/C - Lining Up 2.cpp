#include<bits/stdc++.h>
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
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int T=1;
int n;
struct edge{
	int to,nxt;
}e[300010<<1];
int head[300010],cnt=0;
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	return;
}
void dfs(int u,int fa){
	cout<<u<<' ';
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(to!=fa){
			dfs(to,u);
		}
	}
}
signed main(){
	auto solve=[&](){
		read(n);
		int x;
		int k=0;
		for(int i=1;i<=n;++i){
			read(x);
			if(x!=-1) add(x,i);
			else k=i; 
		}
		dfs(k,0);
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



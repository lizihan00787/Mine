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
int n,m,k;
vector<char> mapp[200010];
map<PII,PII> q;
signed main(){
	auto solve=[&](){
		read(n),read(m),read(k);
		for(int i=1;i<=n;++i){
			mapp[i].push_back('x');
			for(int j=1;j<=m;++j){
				char p;
				cin>>p;
				mapp[i].push_back(p);
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				q[mk(i,j)].first=(q[mk(i-1,j)].first+q[mk(i,j-1)].first-q[mk(i-1,j-1)].first+(mapp[i][j]=='.'?1:0));
				q[mk(i,j)].second=(q[mk(i-1,j)].second+q[mk(i,j-1)].second-q[mk(i-1,j-1)].second+(mapp[i][j]=='x'?1:0));
				cout<<q[mk(i,j)].second<<' ';
			}
			cout<<endl;
		}
		int ans=0x3f3f3f3f;
		for(int i=1;i<=n;++i){
			for(int w=1;w<=m-k+1;++w){
				int l=w,r=w+k-1;
				bool p=1;
				int sum=q[mk(i,r)].first-q[mk(i,l-1)].first-q[mk(i-1,l)].first+q[mk(i-1,l-1)].first;
				int numx=q[mk(i,r)].second-q[mk(i,l-1)].second-q[mk(i-1,l)].second+q[mk(i-1,l-1)].second;
				if(numx==0){
					ans=min(ans,sum);
				}
			}
		}
		for(int i=1;i<=m;++i){
			for(int w=1;w<=n-k+1;++w){
				int l=w,r=w+k-1;
				bool p=1;
				int sum=q[mk(r,i)].first-q[mk(r,i-1)].first-q[mk(l-1,i)].first+q[mk(l-1,i-1)].first;
				int numx=q[mk(r,i)].second-q[mk(r,i-1)].second-q[mk(l-1,i)].second+q[mk(l-1,i-1)].second;
				if(numx==0){
					ans=min(ans,sum);
				}
			}
		}
		if(ans!=0x3f3f3f3f) cout<<ans<<endl;
		else cout<<-1<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



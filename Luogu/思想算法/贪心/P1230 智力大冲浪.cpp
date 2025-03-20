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
using namespace std;
int T=1;
int n,m;
struct node{
	int val,t;
}a[520];
bool cmp(node a,node b){
	return a.val>b.val;
}
int vis[520];
signed main(){
	auto solve=[&](){
		read(m),read(n);
		for(int i=1;i<=n;++i) read(a[i].t);
		for(int i=1;i<=n;++i) read(a[i].val);
		sort(a+1,a+n+1,cmp);
		int ans=0,t=0;
		for(int i=1;i<=n;++i){
			int tag=0;
			for(int j=a[i].t;j;j--){
				if(!vis[j]){
					vis[j]=1;
					tag=1;
					break;
				}
			}
			if(tag==0){
				for(int j=n;j;--j){
					if(!vis[j]){
						vis[j]=1;
						break;
					}
				}
				ans+=a[i].val;
			}
		}
		cout<<m-ans<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



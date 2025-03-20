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
const int Max=1e4;
struct edge{
	int u,v,w;
}e[Max<<1];
int cnt=0;
int f[Max];
bool cmp(edge a,edge b){return a.w>b.w;}
inline int find(int k){
	if(f[k]==k)return k;
	return f[k]=find(f[k]);
}
inline void link(int a,int b){
	f[find(b)]=find(a);
}
signed main(){
	auto solve=[&](){
		read(n);
		int u,v,w;
		for(int i=1;i<n;++i){
			for(int j=i+1;j<=n;++j){
				read(w);
				e[++cnt].u=i,
				e[cnt].v=j;
				e[cnt].w=w;
			}
		}
		for(int i=1;i<=n;++i) f[i]=i;
		sort(e+1,e+cnt+1,cmp);
		int ans=0;
		int po=0;
		for(int i=1;i<=cnt;++i){
			int u=e[i].u,v=e[i].v,w=e[i].w;
			if(find(u)!=find(v)){
				link(u,v);
				po++;
				if(po%2!=0) ans+=w;
			}
		}
		cout<<ans<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



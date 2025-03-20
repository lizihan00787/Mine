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
int n;
int a[1020],val[1020],cnt,p[1020],pos[1020];
vector<PII> ans;
void work(int p1,int p2){
	assert(pos[a[p1]]==p1);assert(pos[a[p2]]=p2);
	pos[a[p1]]=p2;
	pos[a[p2]]=p1;
	swap(a[p1],a[p2]);
	ans.push_back(mk(p1,p2));
}
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i) read(a[i]),val[++cnt]=a[i];
		sort(val+1,val+1+n);
		cnt=unique(val+1,val+n+1)-val-1;
		int x=0;
		for(int v=1;v<=cnt;++v)
			for(int i=1;i<=n;++i)
				if(a[i]==val[v]) p[i]=++x;
		for(int i=1;i<=n;++i) a[i]=p[i];
		assert(x==n);
		for(int i=1;i<=n;++i) pos[a[i]]=i;
		for(int i=n;i>=1;--i){
			for(int j=a[i]+1;j<=i;++j){
				work(pos[j],i);
			}
		}
		printf("%lld\n",ans.size());
		for(int i=0;i<ans.size();++i) printf("%lld %lld\n",ans[i].first,ans[i].second);
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


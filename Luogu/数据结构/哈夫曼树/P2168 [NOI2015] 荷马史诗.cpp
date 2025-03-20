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
priority_queue<PII,vector<PII>,greater<PII > >q;
int n,k;
int ans1=0,ans2=0x3f3f3f3f3f3f3f3f;
signed main(){
	auto solve=[&](){
		read(n),read(k);
		for(int x,i=1;i<=n;++i){
			read(x);
			q.push(mk(x,1));
		}
		int sum=0;
		while((q.size()-1)%(k-1)!=0) q.push(mk(0,1));
		while(q.size()>1){
			int maxdep=0;
			sum=0;
			for(int i=1;i<=k;++i){
				auto tmp=q.top();
				q.pop();
				sum+=tmp.first;
				maxdep=max(maxdep,tmp.second);
				if(q.empty()) break;
			}
			ans1+=sum;
			q.push(mk(sum,maxdep+1));
		}
		cout<<ans1<<endl<<q.top().second-1<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



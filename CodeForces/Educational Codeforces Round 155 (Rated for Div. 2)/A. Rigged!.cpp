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
struct node{
	int s,e,k;
}a[120];
bool cmp(node a,node b){
	if(a.s!=b.s) return a.s>b.s;
	return a.k>b.k;
}
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i) read(a[i].s),read(a[i].e),a[i].k=i;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;++i){
			if(a[i].k==1){
				for(int j=i-1;j>=1;--j){
					if(a[j].e>=a[i].e){
						cout<<-1<<endl;
						return;
					}
				}
				cout<<a[i].s<<endl;
				return;
			}
		}
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}



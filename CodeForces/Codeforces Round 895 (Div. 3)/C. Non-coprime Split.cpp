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
signed main(){
	auto solve=[&](){
		int l,r;
		read(l),read(r);
		if(r<4){
			cout<<-1<<endl;
			return;
		}
		if(l!=r){
			if(r%2==0) cout<<2<<' '<<r-2<<endl;
			else cout<<2<<' '<<r-3<<endl;
			return;
		}
		for(int i=2;i<=sqrt(l);++i){
			if(l%i==0){
				cout<<i<<' '<<l-i<<endl;
				return;
			}
		}
		cout<<-1<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}



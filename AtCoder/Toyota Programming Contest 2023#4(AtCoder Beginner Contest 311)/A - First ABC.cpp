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
char a[120];
signed main(){
	auto solve=[&](){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		bool ca=0,cb=0,cc=0;
		for(int i=1;i<=n;++i){
			if(a[i]=='A') ca=1;
			else if(a[i]=='B') cb=1;
			else if(a[i]=='C') cc=1;
			if(ca==1 && cb==1 && cc==1){
				cout<<i<<endl;
				return;
			}
		}
	};
	while(T--) solve();
	return 0;
}

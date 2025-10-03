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
int mapp[120][120];
signed main(){
	auto solve=[&](){
		cin>>n;
		int a,b,c,d;
		for(int i=1;i<=n;++i){
			cin>>a>>b>>c>>d;
			for(int j=c;j<d;++j){
				for(int k=a;k<b;++k){
					mapp[j][k]=1;
				}
			}
		}
		int ans=0;
		for(int i=0;i<=100;++i){
			for(int j=0;j<=100;++j){
				if(mapp[i][j]==1){
					ans++;
				}
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



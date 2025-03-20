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
int a[1020];
signed main(){
	auto solve=[&](){
		read(n);
		memset(a,0x3f,sizeof(a));
		for(int i=0;i<=n;++i){
			if(i==0){
				a[0]=1;
				continue;
			}
			for(int j=1;j<=9;++j){
				if(n%j==0){
					if(i%(n/j)==0){
						a[i]=min(a[i],j);
					}
				}
			}
		}
		for(int i=0;i<=n;++i){
			if(a[i]!=0x3f3f3f3f3f3f3f3f) cout<<a[i];
			else cout<<'-';
		}
		cout<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



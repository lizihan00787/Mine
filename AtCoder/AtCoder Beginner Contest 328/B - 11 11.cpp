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
int a[120];
signed main(){
	auto solve=[&](){
		read(n);
		int sum=0;
		for(int i=1;i<=n;++i){
			read(a[i]);
			int w=i;
			bool o=1;
			int las=i%10;
			while(w>0){
				int we=w%10;
				if(we!=las){
					o=0;
					break;
				}
				w/=10;
			}
			if(o==0) continue;
			for(int j=1;j<=a[i];++j){
				int k=j;
				bool p=1;
				while(k>0){
					int now=k%10;
					if(now!=las){
						p=0;
						break;
					}
					k/=10;
				}
				if(p==1) sum++;
				
			}
		}
		cout<<sum<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



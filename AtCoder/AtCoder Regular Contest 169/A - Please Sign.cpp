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
const int Max=250000;
int n;
int a[Max];
int p[Max];
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i){
			read(a[i]);
		}
		for(int i=2;i<=n;++i){
			read(p[i]);
		}
		int sum=a[1];
		for(int i=2;i<=n;++i){
			sum+=a[i];
			if(i<=n){
				sum-=a[p[i]];
			}
		}
		if(sum>0) cout<<"+"<<endl;
		else if(sum<0) cout<<"-"<<endl;
		else cout<<0<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



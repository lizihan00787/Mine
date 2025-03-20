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
char a[5020],b[5020];
signed main(){
	auto solve=[&](){
		cin>>a+1;
		cin>>b+1;
		int n=strlen(a+1);
		for(int i=1;i<=n;++i){
			if(a[i]=='0' && b[i]==a[i] && a[i+1]=='1' && b[i+1]==a[i+1]){
				cout<<"YES"<<endl;
				return;
			}
		}
		cout<<"NO"<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}



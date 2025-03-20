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
char s[1000010];
int a[1000010];
signed main(){
	auto solve=[&](){
		read(n);
		cin>>s+1;
		bool p=1;
		for(int i=1;i<=n;++i) a[i]=s[i]-'0';
		for(int i=1;i<n-1;++i){
			if(a[i+1]>=a[i]){
				p=0;
				break;
			}
		}
		if(p==0){
			cout<<-1<<endl;
			return;
		}
		for(int i=1;i<n;++i){
			if(a[i]>=2 && a[i]<=9 && a[i+1]!=1){
				cout<<-1<<endl;
				return;
			}
		}
		int cnt1=0;
		for(int i=1;i<n;++i){
			if(a[i]==1) cnt1++;
		}
		cout<<cnt1+a[n]<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



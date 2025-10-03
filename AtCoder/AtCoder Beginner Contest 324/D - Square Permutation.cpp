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
char s[15];
int a[15];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=a*res;
		a=a*a;
		b>>=1;
	}
	return res;
}
signed main(){
	auto solve=[&](){
		read(n);
		cin>>s;
		for(int i=0;i<n;++i){
			a[i+1]=s[i]-'0';
		}
		sort(a+1,a+n+1);
		int ans=0;
		do{
			int sum=0;
			for(int i=1;i<=n;++i) sum+=a[i]*(int)(qpow(10,n-i));
			int pp=1LL*sqrt(sum);
			if(pp*pp==sum) ans++;
		}while(next_permutation(a+1,a+n+1)); 
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



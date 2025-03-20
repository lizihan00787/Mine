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
int a[420][820];
int n;
const int mod=1e9+7;
int quickpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=a*res,res%=mod;
		a=a*a,a%=mod;
		b>>=1;
	}
	return (res+mod)%mod;
}
int ny(int x){
	return (quickpow(x,mod-2)+mod)%mod;
}
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				read(a[i][j]);
				if(i==j) a[i][j+n]=1;
			}
		}
		for(int i=1;i<=n;++i){
			int k=i;
			for(int j=i+1;j<=n;++j){
				if(abs(a[j][i])>abs(a[k][i])){
					k=j;
				}
			}
			if(a[k][i]==0){
				cout<<"No Solution";
				return;
			}
			if(k!=i) swap(a[i],a[k]);
			int zy=a[i][i];
			int invv=ny(a[i][i]);
			for(int j=1;j<=n*2;++j){
				a[i][j]*=invv;
				a[i][j]=(a[i][j]+mod)%mod;
			}
			for(int j=1;j<=n;++j){
				if(i==j) continue; 
				zy=a[j][i];
				int pl=a[i][k]*zy%mod;
				for(int k=i;k<=n*2;++k){
					a[j][k]-=(a[i][k]*zy);
					a[j][k]=(a[j][k]%mod+mod)%mod;
				}
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=n+1;j<=n*2;++j){
				cout<<a[i][j]<<' ';
			}
			cout<<endl;
		}
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


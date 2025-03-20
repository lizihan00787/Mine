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
int a[600010];
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i) read(a[i]),a[i+n]=a[i];
		int i=1,j=2,k;
		while(i<=n && j<=n){
			for(k=0;k<n && a[i+k]==a[j+k];++k);
			if(k==n) break;
			if(a[i+k]>a[j+k]){
				i=i+k+1;
				if(i==j) i++;
			}
			else{
				j=j+k+1;
				if(i==j) j++;
			}
		}
		for(int p=min(i,j);p<=min(i,j)+n-1;++p){
			cout<<a[p]<<' ';
		}
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



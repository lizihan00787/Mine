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
int a[40];
int q[40][40];
int jy[40][40];
int pd(int l,int r){
	if(l==r) return a[l];
	if(l>r) return 1;
	int sum=0;
	int k=0;
	for(int i=l;i<=r;++i){
		int cnt=0;
		if(!jy[l][i-1] && !jy[i+1][r]) cnt=a[i]+pd(l,i-1)*pd(i+1,r);
		else if(jy[l][i-1] && !jy[i+1][r]) cnt=a[i]+jy[l][i-1]*pd(i+1,r);
		else if(!jy[l][i-1] && jy[i+1][r]) cnt=a[i]+pd(l,i-1)*jy[i+1][r];
		else cnt=a[i]+jy[l][i-1]*jy[i+1][r];
		if(cnt>sum){
			sum=cnt;
			k=i;
		}
	}
	jy[l][r]=sum;
	q[l][r]=k;
	return sum;
}
void print(int l,int r){
	if(l==r){
		cout<<l<<' ';
		return;
	}
	if(l>r) return;
	cout<<q[l][r]<<' ';
	print(l,q[l][r]-1);
	print(q[l][r]+1,r);
}
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i){
			read(a[i]);
		}
		int ans=pd(1,n);
		cout<<ans<<endl;
		print(1,n);
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



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
double a[15][15];
double jz[15][15];
double ans[15];
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n+1;++i){
			for(int j=1;j<=n;++j){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				jz[i][n+1]+=(a[i][j]*a[i][j]-a[i+1][j]*a[i+1][j]);
				jz[i][j]=2*(a[i][j]-a[i+1][j]);
			}
		}
		for(int i=1;i<=n;++i){
			int k=i;
			for(int j=i+1;j<=n;++j){
				if(fabs(jz[j][i])>fabs(jz[k][i])){
					k=j;
				}
			}
			if(k!=i) swap(jz[i],jz[k]);
			double zy=jz[i][i];
			for(int j=1;j<=n+1;++j){
				if(i==j) continue;
				zy=jz[j][i]/jz[i][i];
				for(int k=i;k<=n+1;++k){
					jz[j][k]-=jz[i][k]*zy;
				}
			}
		}
		for(int i=1;i<n;++i){
			printf("%0.3lf ",jz[i][n+1]/jz[i][i]);
		}
		printf("%.3lf\n",jz[n][n+1]/jz[n][n]);
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}




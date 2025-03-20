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
double a[120][120];
double ans[120];
const double eps=1e-7; 
signed main(){
	auto solve=[&](){
		read(n);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n+1;++j){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;++i){
			int k=i;
			for(int j=i+1;j<=n;++j){
				if(fabs(a[j][i])>fabs(a[k][i])){
					k=j;
				}
			}
			if(fabs(a[k][i])<eps){
				cout<<"No Solution";
				return;
			}
			if(k!=i) swap(a[i],a[k]);
			double zy=a[i][i];
			for(int j=i;j<=n+1;++j){
				a[i][j]/=zy;
			}
			for(int j=i+1;j<=n;++j){
				zy=a[j][i];
				for(int k=i;k<=n+1;++k){
					a[j][k]-=a[i][k]*zy;
				}
			}
		}
		ans[n]=a[n][n+1];
		for(int i=n-1;i>=1;--i){
			ans[i]=a[i][n+1];
			for(int j=i+1;j<=n;++j){
				ans[i]-=(a[i][j]*ans[j]);
			}
		}
		for(int i=1;i<=n;++i){
			printf("%.2lf\n",ans[i]);
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



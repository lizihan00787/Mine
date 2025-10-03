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
int n,m;
char a[120][120];
int sum[120];
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) cin>>a[i][j];
		for(int i=1;i<=m;++i){
			bool p=0;
			for(int j=1;j<=n;++j){
				if(a[j][i]=='x'){
					p=1;
					break;
				}
			}
			if(p==0){
				sum[i]=sum[i-1]+1;
			}
			else{
				sum[i]=0;
			}
		}
		cout<<*max_element(sum+1,sum+m+1)<<endl;
	};
	while(T--) solve();
	return 0;
}


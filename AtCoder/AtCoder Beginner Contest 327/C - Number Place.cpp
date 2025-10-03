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
int a[11][11];
signed main(){
	auto solve=[&](){
		for(int i=1;i<=9;++i){
			for(int j=1;j<=9;++j){
				read(a[i][j]);
			}
		}
		for(int i=1;i<=9;++i){
			map<int,int> q;
			for(int j=1;j<=9;++j){
				q[a[i][j]]++;
			}
			for(int j=1;j<=9;++j){
				if(q[j]!=1){
					cout<<"No"<<endl;
					return;
				}
			}
		}
		for(int i=1;i<=9;++i){
			map<int,int> q;
			for(int j=1;j<=9;++j){
				q[a[j][i]]++;
			}
			for(int j=1;j<=9;++j){
				if(q[j]!=1){
					cout<<"No"<<endl;
					return;
				}
			}
		}
		for(int i=1;i<=9;i+=3){
			for(int j=1;j<=9;j+=3){
				map<int,int> q;
				for(int l=i;l<=i+2;++l){
					for(int r=j;r<=j+2;++r){
						q[a[l][r]]++;
					}
				}
				for(int p=1;p<=9;++p){
					if(q[p]!=1){
						cout<<"No"<<endl;
						return;
					}
				}
			}
		}
		cout<<"Yes"<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



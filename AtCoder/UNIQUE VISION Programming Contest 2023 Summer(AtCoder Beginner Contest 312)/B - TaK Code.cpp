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
int n,m;
char mapp[120][120];
signed main(){
	auto solve=[&](){
		cin>>n>>m;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>mapp[i][j];
			}
		}
		for(int i=0;i<=n+1;++i) mapp[i][0]='.',mapp[i][m+1]='.';
		for(int i=0;i<=m+1;++i) mapp[0][i]='.',mapp[n+1][i]='.';
		for(int i=1;i<=n-8;++i){
			for(int j=1;j<=m-8;++j){
				if(mapp[i][j]=='#'){
					int xi=i+5,xj=j+5;
					bool p=0;
					for(int x=xi;x<=min(n,xi+3);++x){
						for(int y=xj;y<=min(m,xj+3);++y){
							if((x==xi || y==xj) && mapp[x][y]!='.'){
								p=1;
								break;
							}
							else if((x!=xi && y!=xj) && mapp[x][y]!='#'){
								p=1;
								break;
							}
						}
					}
					for(int x=i;x<=min(n,i+3);++x){
						for(int y=j;y<=min(m,j+3);++y){
							if((x==i+3 || y==j+3) && mapp[x][y]!='.'){
								p=1;
								break;
							}
							else if((x!=i+3 && y!=j+3) && mapp[x][y]!='#'){
								p=1;
								break;
							}
						}
					}
					if(p==1) continue;
					cout<<i<<' '<<j<<endl;
				}
			}
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



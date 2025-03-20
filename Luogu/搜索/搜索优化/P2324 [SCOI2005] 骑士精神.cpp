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
int a[6][6];
int n=5;
int mb[6][6]={
	0,0,0,0,0,0,
	0,1,1,1,1,1,
	0,0,1,1,1,1,
	0,0,0,2,1,1,
	0,0,0,0,0,1,
	0,0,0,0,0,0,
};
int g(){
	int cnt=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(a[i][j]!=mb[i][j]){
				cnt++;
			}
		}
	}
	return cnt;
}
int xx[8]={1,1,-1,-1,2,2,-2,-2};
int yy[8]={2,-2,2,-2,1,-1,1,-1};
bool pd(int x,int y){
	if(x>=1 && x<=n && y>=1 && y<=n) return 1;
	return 0;
}
bool flag=0;
void dfs(int x,int y,int dep,int maxdep){
	if(dep==maxdep){
		if(!g()) flag=1;
		return;
	} 
	for(int i=0;i<8;++i){
		int nx=x+xx[i];
		int ny=y+yy[i];
		if(!pd(nx,ny)) continue;
		swap(a[nx][ny],a[x][y]);
		int sum=g();
		if(sum+dep<=maxdep) dfs(nx,ny,dep+1,maxdep);
		swap(a[nx][ny],a[x][y]);
	}
}
signed main(){
	auto solve=[&](){
		int qx,qy;
		flag=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				char p;
				cin>>p;
				a[i][j]=(p=='1'?1:0);
				if(p=='*') a[i][j]=2,qx=i,qy=j;
			}
		}
		for(int maxdep=1;maxdep<=15;++maxdep){
				dfs(qx,qy,0,maxdep);
				if(flag){
					cout<<maxdep<<endl;
					return;
				}
		}
		cout<<-1<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}



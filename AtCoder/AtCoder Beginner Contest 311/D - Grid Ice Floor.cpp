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
char mapp[220][220];
int n,m;
int T=1;
struct node{
	int x,y;
};
queue<node> q;
bool vis[220][220];
int xx[4]={0,1,0,-1};
int yy[4]={1,0,-1,0};
int cnt=0;
void bfs(){
	q.push({1,1});
	vis[1][1]=1;
	while(!q.empty()){
		auto node=q.front();
		q.pop();
		int X=node.x;
		int Y=node.y;
		for(int i=0;i<=3;++i){
			int nx=X+xx[i];
			int ny=Y+yy[i];
			if(nx>=1 && nx<=n && ny>=1 && ny<=m && !vis[nx][ny] && mapp[nx][ny]!='#'){
				if(i==0){
					for(int j=Y+1;j<=m+1;++j){
						if(mapp[X][j]=='#' && !vis[X][j]){
							q.push({X,j-1});
							cnt++;
							break;	
						}
						else vis[X][j]=1,cnt++;
					}
				}
				if(i==1){
					for(int j1=X+1;j1<=n+1;++j1){
						if(mapp[j1][Y]=='#' && !vis[j1][Y]){
							q.push({j1-1,Y});
							cnt++;
							break;
						}
						else vis[j1][Y]=1,cnt++;
					}
				}
				if(i==2){
					for(int j2=Y-1;j2>=0;--j2){
						if(mapp[X][j2]=='#' && !vis[X][j2]){
							q.push({X,j2+1});
							cnt++;
							break;
						}
						else vis[X][j2]=1,cnt++;
					}
				}
				if(i==3){
					for(int j3=X-1;j3>=0;--j3){
						if(mapp[j3][Y]=='#' && !vis[j3][Y]){
							q.push({j3+1,Y});
							cnt++;
							break;
						}
						else vis[j3][Y]=1,cnt++;
					}
				}
			}
		}
	}
}
signed main(){
	auto solve=[&](){
		read(n),read(m);
		for(int i=0;i<n;++i){
			for(int j=0;j<m;++j){
				cin>>mapp[i][j];
			}
		}
		n-=2,m-=2;
		bfs();
		int ans=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(vis[i][j]) ans++;
			}
		}
		cout<<ans<<endl<<cnt<<endl;
		return;
	};
	while(T--) solve();
	return 0;
}


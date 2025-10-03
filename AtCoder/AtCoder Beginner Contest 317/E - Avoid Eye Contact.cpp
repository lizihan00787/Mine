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
char mapp[2020][2020];
int n,m;
int xx[4]={1,0,-1,0};
int yy[4]={0,-1,0,1};
map<char,int> fx;
bool vis[2020][2020];
void Init(int x,int y,int fx){
	mapp[x][y]='#';
	int nx=x+xx[fx];
	int ny=y+yy[fx];
	if(nx>=1 && nx<=n && ny>=1 && ny<=m && mapp[nx][ny]=='.') Init(nx,ny,fx);
}
int qx,qy,zx,zy;
struct node{
	int x,y,s;
};
void bfs(int x,int y){
	queue<node> q;
	q.push(node{x,y,0});
	while(!q.empty()){
		int X=q.front().x;
		int Y=q.front().y;
		int S=q.front().s;
		q.pop();
		if(X==zx && Y==zy){
			cout<<S<<endl;
			exit(0);
		}
		for(int i=0;i<=3;++i){
			int nx=X+xx[i];
			int ny=Y+yy[i];
			if(nx>=1 && nx<=n && ny>=1 && ny<=m && !vis[nx][ny] && (mapp[nx][ny]=='.' || mapp[nx][ny]=='G')){
				vis[nx][ny]=1; 
				q.push(node{nx,ny,S+1});
			}
		}
	}
}
signed main(){
	auto solve=[&](){
		read(n),read(m);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>mapp[i][j];
				if(mapp[i][j]=='S') qx=i,qy=j;
				if(mapp[i][j]=='G') zx=i,zy=j;
			}
		}
		fx['v']=0;
		fx['<']=1;
		fx['^']=2;
		fx['>']=3;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(mapp[i][j]!='.' && mapp[i][j]!='S' && mapp[i][j]!='#' && mapp[i][j]!='G'){
					int ff=fx[mapp[i][j]];
					Init(i,j,ff);
				}
			}
		}
		bfs(qx,qy);
		cout<<-1<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



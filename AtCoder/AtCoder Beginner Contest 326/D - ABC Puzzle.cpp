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
int n;
string s1,s2;
set<char> l[6],h[6];
char mapp[7][7];
int xx[4]={1,0};
int yy[4]={0,1};
bool vis[7][7];
char ss[4]={'A','B','C','.'};
bool pd(){
	for(int i=1;i<=n;++i){
		l[i].clear();
		h[i].clear();
		l[i].insert('A');
		l[i].insert('B');
		l[i].insert('C');
		h[i].insert('A');
		h[i].insert('B');
		h[i].insert('C');
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(mapp[i][j]!='.'){
				if(h[i].find(mapp[i][j])!=h[i].end()){
					h[i].erase(mapp[i][j]);
				}
				else return 0;
				if(l[j].find(mapp[i][j])!=l[j].end()){
					l[j].erase(mapp[i][j]);
				}
				else return 0;
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(!h[i].empty() || !l[i].empty()){
			return 0;
		}
	}
	return 1;
}
void dfs(int x,int y){
	vis[x][y]=1;
	cout<<x<<' '<<y<<endl;
	for(int k=0;k<=3;++k){
		int fx=ss[k];
		mapp[x][y]=fx;
		if(x==n && y==n){
			if(pd()==1){
				for(int i=1;i<=n;++i){
					for(int j=1;j<=n;++j){
						cout<<mapp[i][j];
					}
					cout<<endl;
				}
				exit(0);
			}
			else{
				continue;
			}
		}
		int nx=x;
		int ny=y+1;
		if(nx>=2 && nx<=n && ny>=2 && ny<=n && !vis[nx][ny]){
			dfs(nx,ny);
		}
		if(ny>n && nx+1<=n && nx+1>=2 && !vis[nx+1][2]){
			dfs(nx+1,2);
		}
	}
	vis[x][y]=0;
	return;
}
signed main(){
	auto solve=[&](){
		cin.ignore(0);
		read(n);
		getline(cin,s1);
		getline(cin,s2);
		map<char,bool> q;
		if(s1[0]!=s2[0]){
			cout<<"No"<<endl;
			return;
		}
		for(int i=0;i<s1.size();++i){
			if(!q[s1[i]]){
				q[s1[i]]=1;
				mapp[i+1][1]=s1[i];
			}
			else mapp[i+1][1]='.';
		}
		q.clear();
		for(int i=0;i<s2.size();++i){
			if(!q[s2[i]]){
				q[s2[i]]=1;
				mapp[1][i+1]=s2[i];
			}
			else mapp[1][i+1]='.';
		}
		dfs(2,2);
//		for(int i=1;i<=n;++i){
//			for(int j=1;j<=n;++j){
//				cout<<mapp[i][j];
//			}
//			cout<<endl;
//		}
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



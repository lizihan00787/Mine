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
int m;
string s[4];
struct edge{
	int to,nxt;
}e[100010];
int head[1020],cnt=0;
void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
map<int,int> q;
signed main(){
	auto solve=[&](){
		cin>>m;
		cin.ignore();
		getline(cin,s[1]);
		getline(cin,s[2]);
		getline(cin,s[3]);
		s[1]+=s[1];
		s[2]+=s[2];
		s[3]+=s[3];
		s[1]+=s[1];
		s[2]+=s[2];
		s[3]+=s[3];
		int minn=0x3f3f3f3f;
		for(char p='0';p<='9';++p){
			q.clear();
			int maxx=0;
			for(int k=1;k<=3;++k)
			for(int i=0;i<3*m;++i){
				if(s[k][i]==p && q[i]==0){
					q[i]=1;
					maxx=max(maxx,i);
					break;
				}
			}
			minn=min(minn,maxx);
		}
		if(minn!=0) cout<<minn<<endl;
		else cout<<-1<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



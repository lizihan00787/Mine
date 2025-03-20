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
const int N=2e5+20;
pqd q1;
pqx q2;
int n,m;
int a[N],b[N];
signed main(){
	auto solve=[&](){
		read(n),read(m);
		for(int i=1;i<=n;++i) read(a[i]);
		for(int i=1;i<=m;++i) read(b[i]);
		int p=0;
		for(int i=1;i<=m;++i){
			while(p<b[i]){
				p++;
				q1.push(a[p]);
				q2.push(q1.top());
				q1.pop();
			}
			cout<<q2.top()<<endl;
			q1.push(q2.top());
			q2.pop();
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



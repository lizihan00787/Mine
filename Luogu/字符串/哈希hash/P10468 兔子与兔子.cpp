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
unsigned int b[1000010],mi[1000010];
char a[1000010];
int m;
const int base=131;
signed main(){
	auto solve=[&](){
		cin>>a+1;
		read(m);
		mi[0]=1;
		int n=strlen(a+1);
		for(int i=1;i<=n;++i){
			b[i]=b[i-1]*base+a[i]-'a';
			mi[i]=mi[i-1]*base;
		}
		while(m--){
			int l1,r1,l2,r2;
			read(l1),read(r1),read(l2),read(r2);
			if(b[r1]-b[l1-1]*mi[r1-l1+1]==b[r2]-b[l2-1]*mi[r2-l2+1])cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
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



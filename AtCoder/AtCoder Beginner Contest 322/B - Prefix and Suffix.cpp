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
string s1,s2;
signed main(){
	auto solve=[&](){
		read(n),read(m);
		getline(cin,s1),getline(cin,s2);
		bool f1=1,f2=1;
		for(int i=0;i<s1.size();++i){
			if(s1[i]!=s2[i]){
				f1=0;
				break;
			}
		}
		reverse(s1.begin(),s1.end());
		reverse(s2.begin(),s2.end());
		for(int i=0;i<s1.size();++i){
			if(s1[i]!=s2[i]){
				f2=0;
				break;
			}
		}
		if(f1==1 && f2==1) cout<<0<<endl;
		else if(f1==1 && f2==0) cout<<1<<endl;
		else if(f1==0 && f2==1) cout<<2<<endl;
		else cout<<3<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



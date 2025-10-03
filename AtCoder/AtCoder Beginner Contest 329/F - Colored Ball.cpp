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
int n,q;
int a[200010];
unordered_set<int> s[200010];
unordered_map<int,int> siz;
signed main(){
	auto solve=[&](){
		read(n),read(q);
		for(int i=1;i<=n;++i){
			read(a[i]);
			s[i].insert(a[i]);
			siz[i]=1;
		}
		for(int i=1;i<=q;++i){
			int a,b;
			read(a),read(b);
			if(s[a].size()<=s[b].size()){
				for(auto it:s[a]){
					s[b].insert(it);
				}
				s[a].clear();
			}
			else{
				for(auto it:s[b]){
					s[a].insert(it);
				}
				s[b].clear();
				swap(s[a],s[b]);
			}
			cout<<s[b].size()<<endl;
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



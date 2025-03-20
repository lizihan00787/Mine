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
map<char,int> q;
string s;
signed main(){
	auto solve=[&](){
		cin.ignore(0);
		read(n);
		getline(cin,s);
		int ans=1;
		int cnt=1;
		for(int i=1;i<n;++i){
			if(s[i]!=s[i-1]) q[s[i-1]]=max(q[s[i-1]],cnt);
			if(s[i]!=s[i-1]) cnt=1;
			else cnt++;
			if(!q[s[i]] || cnt>q[s[i]]) ans++;
		}
		cout<<ans<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



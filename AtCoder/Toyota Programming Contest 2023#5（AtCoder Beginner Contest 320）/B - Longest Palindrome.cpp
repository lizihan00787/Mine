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
string s;
signed main(){
	auto solve=[&](){
		getline(cin,s);
		int maxx=0;
		for(int i=0;i<s.size();++i){
			for(int j=i;j<s.size();++j){
				string s1,s2;
				for(int k=i;k<=j;++k){
					s1.push_back(s[k]);
				}
				for(int k=j;k>=i;--k){
					s2.push_back(s[k]);
				}
				if(s1==s2){
					maxx=max(maxx,j-i+1);
				}
			}
		}
		cout<<maxx<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



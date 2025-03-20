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
char a[200010];
signed main(){
	auto solve=[&](){
		cin>>a+1;
		int now=0,s1=1,s2=0x3f3f3f3f;
		for(int i=1;i<=strlen(a+1);++i){
			if(a[i]=='+') now++;
			else if(a[i]=='-'){
				now--;
				if(now>0 && s1>now) s1=now;
				if(s2>now) s2=0x3f3f3f3f;
			}
			else if(a[i]=='1'){
				if(s2<=now){
					cout<<"NO"<<endl;
					return;
				}
				s1=max(s1,now);
			}
			else{
				if(s1>=now){
					cout<<"NO"<<endl;
					return;
				}
				s2=min(s2,now);
			}
		}
		cout<<"YES"<<endl;
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(T);
	while(T--) solve();
	return 0;
}



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
int s,t,n;
char a[30];
int b[30];
signed main(){
	auto solve=[&](){
		read(s),read(t),read(n);
		cin>>a+1;
		for(int i=1;i<=n;++i) b[i]=a[i]-'a'+1;
		int www=5;
		while(www--){
			b[n]++;
			if(b[n]>t){
				for(int j=n-1;j>=1;--j){
					if(b[j]<t-(n-j)){
						b[j]++;
						for(int k=j+1;k<=n;++k){
							b[k]=b[j]+(k-j);
						}
						break;
					}
				}
			}
			for(int i=1;i<=n;++i){
				cout<<char(b[i]-1+'a');
			}
			cout<<endl;
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



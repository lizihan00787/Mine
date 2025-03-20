#include<bits/stdc++.h>
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
int T=1;
int n;
char s[200010];
int f[200010];
vector<int> g;
signed main(){
	auto solve=[&](){
		cin>>n>>s+1;
		for(int i=1;i<n;++i){
			if(!(n%i)){
				g.push_back(i),f[i]=1;
				for(int j=1;j<=i;++j){
					bool fl=1;
					for(int k=1;k<=n/i;++k){
						fl&=(s[(k-1)*i+j]=='#');
					}
					if(fl) f[i]=f[i]*2%MOD;
				}
			}
		}
		int ans=0;
		for(int x:g){
			for(int y:g){
				if(y<x && !(x%y)) (f[x]-=f[y])%=MOD;
			}
			(ans+=f[x])%MOD;
		}
		cout<<(ans+MOD)%MOD;
	};
	io();

	while(T--) solve();
	return 0;
}



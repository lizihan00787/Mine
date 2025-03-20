#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
int x,y,z;
char a[300010];
int dp[300010][2];
signed main(){
	auto solve=[&](){
		cin>>x>>y>>z;
		cin>>a+1;
		int n=strlen(a+1);
		dp[1][0]=(a[1]>='A' && a[1]<='Z')?y:x;
		dp[1][1]=(a[1]>='A' && a[1]<='Z')?x+z:z+y;
		for(int i=2;i<=n;++i){
			dp[i][0]=min(dp[i-1][0]+((a[i]>='A' && a[i]<='Z')?y:x),dp[i-1][1]+((a[i]>='A' && a[i]<='Z')?y+z:x+z));
			dp[i][1]=min(dp[i-1][0]+((a[i]>='A' && a[i]<='Z')?z+x:z+y),dp[i-1][1]+((a[i]>='A' && a[i]<='Z')?x:y));
		}
		cout<<min(dp[n][1],dp[n][0])<<endl;
	};
	io();

	while(T--) solve();
	return 0;
}



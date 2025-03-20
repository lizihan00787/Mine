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
const int N=20;
int n,m,a[N][N],dp[1<<N][N];
signed main(){
	auto solve=[&](){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
	        int x,y,z;
	        scanf("%d%d%d",&x,&y,&z);
	        a[x][y]=a[y][x]=z;
	    }
	    for(int s=0;s<(1<<n);s++)
	        for(int i=0;i<n;i++)
	            if(s&(1<<i))
	                for(int j=0;j<n;j++)
	                    if(s&(1<<j))
	                        dp[s][i]=max(dp[s][i],dp[s^(1<<i)][j]+a[j][i]);
	    int ans=0;
	    for(int i=0;i<n;i++)
	        ans=max(ans,dp[(1<<n)-1][i]);
	    printf("%d\n",ans);
		return;
	};
//	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}



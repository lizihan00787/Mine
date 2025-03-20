#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
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
int a[60][60];
int dp[60][60][60][60];
signed main(){
    auto solve=[&](){
        read(n);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                char p;
                cin>>p;
                a[i][j]=(p=='#'?1:0);
                dp[i][j][i][j]=(p=='#'?1:0);
            }
        }
        for(int len1=1;len1<=n;++len1){
            for(int len2=1;len2<=n;++len2){
                for(int i=1;i+len1-1<=n;++i){
                    for(int j=1;j+len2-1<=n;++j){
                        int x=i+len1-1,y=j+len2-1;
                        for(int k=i;k<x;++k) dp[i][j][x][y]=min(dp[i][j][x][y],dp[i][j][k][y]+dp[k+1][j][x][y]);
                        for(int k=j;k<y;++k) dp[i][j][x][y]=min(dp[i][j][x][y],dp[i][j][x][k]+dp[i][k+1][x][y]);
                        dp[i][j][x][y]=min(dp[i][j][x][y],max(len1,len2));
                    }
                }
            }
        }
        cout<<dp[1][1][n][n]<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
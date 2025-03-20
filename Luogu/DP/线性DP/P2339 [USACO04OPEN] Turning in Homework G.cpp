#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
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
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1020;

int n,m,zd;
struct node{
    int tim,x;
    bool operator < (const node &a) const{
        return x<a.x;
    }
}a[N];
int dp[N][N][2];

signed main(){
    auto solve=[&](){
        read(n),read(m),read(zd);
        for(int i=1;i<=n;++i) read(a[i].x),read(a[i].tim);
        sort(a+1,a+n+1);
        memset(dp,0x3f,sizeof(dp));
        dp[1][n][0]=max(a[1].x,a[1].tim);
        dp[1][n][1]=max(a[n].x,a[n].tim);
        for(int i=1;i<=n;++i){
            for(int j=n;j>=i;--j){
                dp[i][j][0]=min(dp[i][j][0],max(dp[i-1][j][0]+a[i].x-a[i-1].x,a[i].tim));
                dp[i][j][0]=min(dp[i][j][0],max(dp[i][j+1][1]+a[j+1].x-a[i].x,a[i].tim));
                dp[i][j][1]=min(dp[i][j][1],max(dp[i][j+1][1]+a[j+1].x-a[j].x,a[j].tim));
                dp[i][j][1]=min(dp[i][j][1],max(dp[i-1][j][0]+a[j].x-a[i-1].x,a[j].tim));
            }
        }
        int ans=0x3f3f3f3f;
        for(int i=1;i<=n;++i)
            ans=min(ans,min(dp[i][i][0]+abs(a[i].x-zd),dp[i][i][1]+abs(a[i].x-zd)));
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
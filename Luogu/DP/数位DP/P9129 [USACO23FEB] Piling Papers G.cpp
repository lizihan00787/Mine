#include<bits/stdc++.h>
#define endl '\n'
#define int long long
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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=320,M=5e4+20,mod=1e9+7;

int n,A,B,a[N];
int ans[N][N][2];
int dp[N][N][3];
int num[N];
int q;

inline void add(int &x,int y) {(x+y>=mod)?x+=y-mod:x+=y;}
inline int cmp(int x,int y) {return x==y?2:x>y;}

void calc(int x,bool p){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    reverse(num+1,num+len+1);
    for(int l=1;l<=n;++l){
        for(int i=0;i<20;++i) for(int j=0;j<20;++j) dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=0;
        for(int r=l;r<=n;++r){
            for(int i=1;i<=len;++i)
                for(int j=len;j>i;--j){
                    if(a[r]==num[i]) for(int k=0;k<3;++k) add(dp[i][j][k],dp[i+1][j][k]);
                    else for(int k=0;k<3;++k) add(dp[i][j][a[r]>num[i]],dp[i+1][j][k]);
                    add(dp[i][j][0],dp[i][j-1][0]);
                    add(dp[i][j][1],dp[i][j-1][1]);
                    add(dp[i][j][cmp(a[r],num[j])],dp[i][j-1][2]);
                }
            for(int i=1;i<=len;++i) add(dp[i][i][cmp(a[r],num[i])],2);
            for(int i=1;i<=len;++i){
                add(ans[l][r][p],dp[i][len][0]);
                add(ans[l][r][p],dp[i][len][2]);
                if(i>1) add(ans[l][r][p],dp[i][len][1]);
            }
        }
    }
}

inline void solve(){
    read(n,A,B);
    for(int i=1;i<=n;++i) read(a[i]);
    calc(A-1,0),calc(B,1);
    read(q);
    while(q--){
        int l,r;
        read(l,r);
        cout<<(ans[l][r][1]-ans[l][r][0]+mod)%mod<<endl; 
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
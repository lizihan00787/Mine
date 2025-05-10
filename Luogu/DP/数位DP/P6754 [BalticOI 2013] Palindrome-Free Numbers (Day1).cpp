#include<bits/stdc++.h>
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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

int A,B;
int num[20];
int dp[20][11][11][2];

int dfs(int now,bool op0,bool lim,int pre1,int pre2,bool flag){
    int res=0,up=(lim)?num[now]:9;
    if(now==0) return flag;
    if(!lim && !op0 && pre1!=-1 && pre2!=-1 && dp[now][pre1][pre2][flag]!=-1) return dp[now][pre1][pre2][flag];
    for(int i=0;i<=up;++i)
        res=(res+dfs(now-1,(op0 && i==0),(lim && i==up),(op0 && !i)?-1:i,(op0)?-1:pre1,flag||(!op0&&(i==pre1))||(!op0&&(i==pre2))));
    if(!lim && !op0 && pre1!=-1 && pre2!=-1) dp[now][pre1][pre2][flag]=res;
    return res;
}
int work(int x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len,1,1,-1,-1,0);
}

signed main(){
    auto solve=[&](){
        read(A),read(B);
        cout<<B-A-work(B)+work(A-1)+1<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
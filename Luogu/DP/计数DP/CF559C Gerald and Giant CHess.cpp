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
const int mod=1e9+7;
int h,w,n;
struct node{
    int x,y;
}a[300050];
bool cmp(node a,node b){ return a.x<b.x||(a.x==b.x&&a.y<b.y); }
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int inv(int a){
    return qpow(a,mod-2);
}
int dp[300050];
int jc[300050];
int bal(int n,int m){
    if(m>n) return 0;
    return (jc[n]*inv(jc[m])%mod*inv(jc[n-m])%mod+mod)%mod;
}
signed main(){
    auto solve=[&](){
        read(h),read(w),read(n);
        jc[0]=1;
        for(int i=1;i<=300000;++i) jc[i]=jc[i-1]*i%mod;
        for(int i=1;i<=n;++i) read(a[i].x),read(a[i].y);
        a[n+1].x=h,a[n+1].y=w;
        sort(a+1,a+n+2,cmp);
        for(int i=1;i<=n+1;++i) dp[i]=(bal(a[i].x+a[i].y-2,a[i].x-1)%mod+mod)%mod;
        for(int i=1;i<=n+1;++i){
            for(int j=1;j<=i-1;++j){
                if(a[i].x<a[j].x || a[i].y<a[j].y) continue;
                dp[i]=(dp[i]-dp[j]*bal(a[i].x+a[i].y-a[j].x-a[j].y,a[i].x-a[j].x)%mod+mod)%mod;
            }
        }
        cout<<(dp[n+1]%mod+mod)%mod<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
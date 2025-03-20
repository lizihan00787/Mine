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
int f[200][200];
int num[1000010];
int a,b;
const int mod=1e9+7;
int dfs(int now,int sum,bool lim){
    if(now==0) return sum;
    int res=0;
    if(f[now][sum]>=0 && !lim) return f[now][sum]%mod;
    int upp=lim?num[now]:9;
    for(int i=0;i<=upp;++i){
        res+=dfs(now-1,sum+i,lim && i==num[now]);
        res%=mod;
    }
    if(!lim) f[now][sum]=res%mod;
    return res%mod;
}
int work(int sum){
    int len=0;
    while(sum){
        num[++len]=sum%10;
        sum/=10;
    }
    memset(f,-1,sizeof(f));
    return dfs(len,0,1)%mod;
}
signed main(){
    auto solve=[&](){
        read(a),read(b);
        int ans=0;
        ans+=work(b)-work(a-1)+mod;
        ans%=mod;
        cout<<ans<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    read(T);
    while(T--) solve();
    return 0;
}
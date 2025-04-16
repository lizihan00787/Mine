#include<bits/stdc++.h>
#define endl '\n'
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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=5e3+20,M=12,mod=998244353;

ll n,m,k;
char s[N],t[M];
ll dp[N][M][M];
ll inv[M],ans;

ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;b>>=1;
    }
    return res;
}
ll C(ll x){
	ll res=1;
	for(int i=0;i<x;i++) (res*=(k-i)%mod)%=mod;
	return res*inv[x]%mod;
}

void dfs(int l,int pos,ll tot){
    if(l>m) return (ans+=tot*C(pos))%=mod,void();
    for(int r=l;r<=m;++r) dfs(r+1,pos+1,tot*dp[n][l][r]%mod);
}

inline void solve(){
    read(k);
    inv[1]=1;
	for(int i=2;i<=10;i++) inv[i]=inv[i-1]*qpow(i,mod-2)%mod;
    scanf("%s%s",s+1,t+1);
    n=strlen(s+1),m=strlen(t+1);
    for(int i=1;i<=n;++i){
        for(int l=1;l<=m;++l){
            for(int r=l;r<=m;++r){
                dp[i][l][r]=dp[i-1][l][r];
                if(s[i]==t[r]) dp[i][l][r]+=(l==r)?1:dp[i-1][l][r-1],dp[i][l][r]%=mod;
            }
        }
    }
    dfs(1,0,1);
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
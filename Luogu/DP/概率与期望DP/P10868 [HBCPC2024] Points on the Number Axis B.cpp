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

const int N=1e6+20,mod=998244353,in=499122177;

int n;
int fac[N],inv[N],f[N];

int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;b>>=1;
    }
    return res;
}

int binom(int n,int m){
    if(n<m) return 0;
    return fac[n]*inv[n-m]%mod*inv[m]%mod;
}

inline void solve(){
    read(n);
    inv[0]=fac[0]=f[0]=1;
    for(int i=1;i<N;++i) f[i]=f[i-1]*(i-in+mod)%mod,fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for(int i=N-2;i>=1;--i) inv[i]=inv[i+1]*(i+1)%mod;
    int ans=0;
    for(int i=1;i<=n;++i){
        int x;
        read(x);
        int tmp=binom(n-1,i-1)*f[i-1]%mod*f[n-i]%mod;
        ans=(ans+tmp*inv[n-1]%mod*x%mod)%mod;
    }
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
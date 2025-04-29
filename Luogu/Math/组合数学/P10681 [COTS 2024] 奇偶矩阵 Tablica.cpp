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

const int N=3e3+20,mod=1e9+7;

int fac[N<<1],inv[N<<1],n,m,ans,C[N][N];

int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}

int calc(int b,int c,int d){
    int res=0;
    for(int t=0;t<=min(d,b);++t) res=(res+((t&1)?(mod-1):1)*C[b][t]%mod*C[d][t]%mod*fac[t]%mod*fac[c+2*d-2*t]%mod*inv[b+d-t]%mod)%mod;
    return res;
}

inline void solve(){    
    read(n),read(m);
    fac[0]=inv[0]=1;
    int s=2*max(n,m),i2=qpow(2,mod-2);
    for(int i=1;i<=s;++i) fac[i]=fac[i-1]*i%mod,inv[i]=inv[i-1]*i2%mod;
    for(int i=0;i<=max(n,m);++i){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
    for(int b=0;b<=n;++b){
        int a=n-b,cnt=2*b+a;
        if(cnt>=m && cnt<=2*m) ans=(ans+C[n][b]*C[m][cnt-m]%mod*calc(b,2*m-cnt,cnt-m)%mod)%mod;
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
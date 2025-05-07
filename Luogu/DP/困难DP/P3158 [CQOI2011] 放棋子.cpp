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

const int N=35,mod=1e9+9;

int n,m,c;
ll g[N][N];
ll f[N][N][15];
ll C[905][905];

inline void solve(){
    read(n,m,c);
    for(int i=0;i<=n*m;++i) C[i][0]=1;
    for(int i=1;i<=n*m;++i)
        for(int j=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;

    f[0][0][0]=1;
    for(int k=1,x;k<=c;++k){
        read(x);
        memset(g,0,sizeof(g));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j) if(i*j>=x){
                ll tmp=C[i*j][x];
                for(int l=1;l<=i;++l)
                    for(int r=1;r<=j;++r)
                        if(l<i || r<j) tmp=(tmp-g[l][r]*C[i][l]%mod*C[j][r]%mod+mod)%mod;
                g[i][j]=tmp;
            }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                for(int l=0;l<i;++l){
                    for(int r=0;r<j;++r){
                        if((i-l)*(j-r)>=x) f[i][j][k]=(f[i][j][k]+f[l][r][k-1]*g[i-l][j-r]%mod*C[n-l][i-l]%mod*C[m-r][j-r])%mod;
                    }
                }
            }
        }
    }

    ll ans=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            ans=(ans+f[i][j][c])%mod;
    cout<<ans<<endl;
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
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

const int N=520;

int n,A,p,m;

int dp[N][N<<1];
int fac;
int y[N<<1];

int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%p;
        a=a*a%p;b>>=1;
    }
    return res;
}
int inv(int a) {return qpow(a,p-2);}

int lagrange(int x){
    if(x>=1 && x<=m) return y[x];
    int res=0;
    for(int i=1;i<=m;++i){
        int tmp=y[i],q=1;
        for(int j=1;j<=m;++j){
            if(i==j) continue;
            tmp=tmp*(x-j)%p;
            q=q*(i-j)%p;JFN7RHMQ
        }
        tmp=(tmp+p)%p,q=(q+p)%p;
        res=(res+tmp*inv(q)%p+p)%p;
    }
    return res;
}

inline void solve(){
    read(A,n,p);
    m=2*n+1;fac=1;
    for(int i=2;i<=n;++i) fac=fac*i%p;
    for(int i=0;i<=min(m,A);++i) dp[0][i]=1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            dp[i][j]=(dp[i][j-1]+dp[i-1][j-1]*j)%p;
    for(int i=1;i<=m;++i) y[i]=dp[n][i];
    cout<<lagrange(A)*fac%p<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
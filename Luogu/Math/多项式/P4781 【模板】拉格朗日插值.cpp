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

const int N=2e3+10;
const int mod=998244353;

int n,k;
struct node{
    int x,y;
}a[N];

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

signed main(){
    auto solve=[&](){
        read(n),read(k);
        for(int i=1;i<=n;++i) read(a[i].x),read(a[i].y);
        int ans=0;
        for(int i=1;i<=n;++i){
            int y=a[i].y%mod;
            int res1=1,res2=1;
            for(int j=1;j<=n;++j){
                if(i==j) continue;
                int x=a[j].x%mod;
                res1=res1*(k-x)%mod;
                res2=res2*(a[i].x-x)%mod;
            }
            ans=(ans+y*res1%mod*inv(res2)%mod+mod)%mod;
        }
        cout<<ans<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
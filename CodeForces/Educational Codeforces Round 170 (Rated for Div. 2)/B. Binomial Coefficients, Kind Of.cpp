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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1e5+10,mod=1e9+7;

int t;
int n[N],k[N];

int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

signed main(){
    auto solve=[&](){
        read(t);
        for(int i=1;i<=t;++i) read(n[i]);
        for(int i=1;i<=t;++i) read(k[i]);
        for(int i=1;i<=t;++i) cout<<qpow(2,k[i])%mod<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
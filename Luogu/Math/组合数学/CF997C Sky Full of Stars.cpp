#include<bits/stdc++.h>
#define int long long
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
const int mod=998244353;
int n;
int jc[1000010];
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=a*res,res%=mod;
        a=a*a;a%=mod;
        b>>=1;
    }
    return res;
}
int inv(int a){
    return qpow(a,mod-2);
}
int bal(int n,int m){
    return jc[n]*inv(jc[m])%mod*inv(jc[n-m])%mod;
}
signed main(){
    auto solve=[&](){
        read(n);
        jc[0]=1;
        for(int i=1;i<=n;++i) jc[i]=jc[i-1]*i,jc[i]%=mod;
        int ans=0;
        for(int i=1;i<=n;++i) ans=(ans+qpow(3,(n*(n-i)+i))*qpow(-1,i+1)%mod*bal(n,i)%mod+mod)%mod;
        ans=ans*2%mod;
        int tmp=0;
        for(int i=0;i<n;++i){
            int t=-qpow(3,i);
            tmp=(tmp+bal(n,i)*qpow(-1,i+1)%mod*(qpow(1+t,n)-qpow(t,n)+mod)%mod+mod)%mod;
        }
        ans=(ans+tmp*3)%mod;
        cout<<ans<<endl;
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}
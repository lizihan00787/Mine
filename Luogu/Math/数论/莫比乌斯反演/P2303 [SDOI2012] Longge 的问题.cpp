#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
ll n;
ll getphi(ll n){
    ll ans=n;
    for(ll i=2ll;i*i<=n;i++){
        if(n%i==0) ans=ans/i*(i-1);
        while(n%i==0) n/=i;
    }
    if(n>1) ans=ans/n*(n-1);
    return ans;
}
signed main(){
    auto solve=[&](){
        read(n);
        ll ans=0ll;
        for(ll i=1ll;i*i<=n;++i){
            if(n%i==0ll){
                ll a=i,b=n/i;
                if(a!=b){
                    ans+=getphi(a)*(ll)(n/a);
                    ans+=getphi(b)*(ll)(n/b);
                }
                else ans+=getphi(a)*(ll)(n/a);
            }
        }
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
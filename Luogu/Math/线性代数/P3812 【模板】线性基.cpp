#include<bits/stdc++.h>
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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=52;

int n;
ll a[N];
ll w[N<<1];

void ins(ll x){
    for(int i=61;~i;--i){
        if(!(x>>(ll)i)) continue;
        if(!w[i]) {w[i]=x;break;}
        x^=w[i];
    }
}

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) read(a[i]),ins(a[i]);
        ll ans=0;
        for(int i=61;~i;--i){
            if(!w[i]) continue;
            ans=max(ans,ans^w[i]);
        }
        cout<<ans<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}

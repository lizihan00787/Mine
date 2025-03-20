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

const int N=2e5+10;

int n,k;
int a[N];

inline void solve(){
    read(n,k);
    for(int i=1;i<=n;++i) read(a[i]);
    sort(a+1,a+n+1,greater<int>());
    int ans=0;
    for(int i=1;i<=n;++i){
        if(i&1) ans+=a[i];
        else{
            int cz=min(k,a[i-1]-a[i]);
            a[i]+=cz;
            k-=cz;
            ans-=a[i];
        }
    }
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}
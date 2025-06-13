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

const int N=1e6+20;

int n;
int a[N],c[N];
int ans,mid;

inline void solve(){
    read(n);
    int sum=0;
    for(int i=1;i<=n;++i) read(a[i]),sum+=a[i];
    sum/=n;
    for(int i=1;i<=n;++i) c[i]=c[i-1]+sum-a[i-1];
    sort(c+1,c+n+1);
    mid=c[(n+1)/2];
    for(int i=1;i<=n;++i) ans+=abs(mid-c[i]);
    cout<<ans<<endl;

}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
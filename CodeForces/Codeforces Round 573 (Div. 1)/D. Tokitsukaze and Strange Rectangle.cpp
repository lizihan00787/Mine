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

const int N=2e5+20;

int n,nn;
struct node{
    int x,y;
    bool operator < (const node &a)const{
        if(y!=a.y) return y>a.y;
        return x>a.x;
    }
}a[N];
int tmp[N];

namespace Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    int t[N<<2];
    void update(int k,int rt=1,int l=1,int r=nn){
        if(l==r) return (void)(t[rt]=1);
        int mid=(l+r)>>1;
        if(k<=mid) update(k,lson,l,mid);
        else update(k,rson,mid+1,r);
        t[rt]=t[lson]+t[rson];
    }
    int query(int L,int R,int rt=1,int l=1,int r=nn){
        if(L<=l & r<=R) return t[rt];
        int mid=(l+r)>>1,res=0;
        if(L<=mid) res+=query(L,R,lson,l,mid);
        if(R>mid) res+=query(L,R,rson,mid+1,r);
        return res;
    }
}
using namespace Stree;

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i].x,a[i].y),tmp[i]=a[i].x;
    sort(tmp+1,tmp+n+1);
    nn=unique(tmp+1,tmp+n+1)-tmp-1;
    for(int i=1;i<=n;++i) a[i].x=lower_bound(tmp+1,tmp+nn+1,a[i].x)-tmp;
    sort(a+1,a+n+1);
    ll ans=0;
    for(int i=1;i<=n;++i){
        update(a[i].x);
        ans+=1ll*query((a[i+1].y==a[i].y?a[i+1].x+1:1),a[i].x)*query(a[i].x,nn);
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
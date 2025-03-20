#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
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
#define lson (rt<<1)
#define rson (rt<<1|1)
const int Max=1e6+10;
ll n,x1,x2,y_,y2,X[Max<<1];
int cnt=0;
struct line{
    ll l,r,h;
    int flag;
    bool operator < (const line &a) const{
        return h<a.h;
    }
}lin[Max<<1];
struct Stree{
    struct node{
        int l,r,sum;
        ll len;
    }t[Max<<2];
    void pushup(int rt){
        if(t[rt].sum) t[rt].len=X[t[rt].r+1]-X[t[rt].l];
        else t[rt].len=t[lson].len+t[rson].len;
    }
    void build(int rt,int l,int r){
        t[rt].l=l,t[rt].r=r;
        t[rt].sum=0;
        t[rt].len=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
    }
    void update(int rt,ll L,ll R,int v){
        if(X[t[rt].r+1]<=L || R<=X[t[rt].l]) return;
        if(L<=X[t[rt].l] && X[t[rt].r+1]<=R){
            t[rt].sum+=v;
            pushup(rt);
            return;
        }
        update(lson,L,R,v);
        update(rson,L,R,v);
        pushup(rt);
    }
}Q;
signed main(){
    read(n);
    for(int i=1;i<=n;++i){
        read(x1),read(y_),read(x2),read(y2);
        X[(i<<1)-1]=x1,X[(i<<1)]=x2;
        lin[(i<<1)-1]={x1,x2,y_,1};
        lin[(i<<1)]={x1,x2,y2,-1};
    }
    n=n<<1;
    sort(lin+1,lin+n+1);
    sort(X+1,X+n+1);
    int k=unique(X+1,X+n+1)-(X+1);
    Q.build(1,1,k-1);
    ll ans=0;
    for(int i=1;i<n;++i){
        Q.update(1,lin[i].l,lin[i].r,lin[i].flag);
        ans+=Q.t[1].len*(lin[i+1].h-lin[i].h);
    }
    cout<<ans<<endl;
    return 0;
}

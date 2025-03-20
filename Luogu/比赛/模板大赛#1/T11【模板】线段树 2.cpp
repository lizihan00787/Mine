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

const int N=1e5+10;

int n,q,m;
int a[N];

struct Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node{
        int sum,add,mul;
    }t[N<<2];
    void pushup(int rt){
        t[rt].sum=(t[lson].sum+t[rson].sum)%m;
    }
    void build(int rt,int l,int r){
        t[rt].add=0,t[rt].mul=1;
        if(l==r) {t[rt].sum=a[l];return;}
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
        pushup(rt);
    }
    void pushdown(int rt,int l,int r){
        int mid=(l+r)>>1;
        t[lson].sum=(t[lson].sum*t[rt].mul+t[rt].add*(mid-l+1))%m;
        t[rson].sum=(t[rson].sum*t[rt].mul+t[rt].add*(r-mid))%m;
        t[lson].mul=(t[lson].mul*t[rt].mul)%m;
        t[rson].mul=(t[rson].mul*t[rt].mul)%m;
        t[lson].add=(t[rt].mul*t[lson].add+t[rt].add)%m;
        t[rson].add=(t[rt].mul*t[rson].add+t[rt].add)%m;
        t[rt].mul=1,t[rt].add=0;
    }
    void update1(int rt,int l,int r,int L,int R,int k){
        if(L<=l && r<=R){
            t[rt].sum=(t[rt].sum+(r-l+1)*k)%m;
            t[rt].add=(t[rt].add+k)%m;
            return;
        }
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(L<=mid) update1(lson,l,mid,L,R,k);
        if(R>mid) update1(rson,mid+1,r,L,R,k);
        pushup(rt);
    }
    void update2(int rt,int l,int r,int L,int R,int k){
        if(L<=l && r<=R){
            t[rt].sum=(t[rt].sum*k)%m;
            t[rt].add=(t[rt].add*k)%m;
            t[rt].mul=(t[rt].mul*k)%m;
            return;
        }
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(L<=mid) update2(lson,l,mid,L,R,k);
        if(R>mid) update2(rson,mid+1,r,L,R,k);
        pushup(rt);
    }
    int query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R) return t[rt].sum;
        pushdown(rt,l,r);
        int mid=(l+r)>>1,res=0;
        if(L<=mid) res+=query(lson,l,mid,L,R),res%=m;
        if(R>mid) res+=query(rson,mid+1,r,L,R),res%=m;
        return res;
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(q),read(m);
        for(int i=1;i<=n;++i) read(a[i]);
        Q.build(1,1,n);
        for(int i=1;i<=q;++i){
            int op,l,r,k;
            read(op);
            if(op==1){
                read(l),read(r),read(k);
                Q.update2(1,1,n,l,r,k);
            }
            else if(op==2){
                read(l),read(r),read(k);
                Q.update1(1,1,n,l,r,k);
            }
            else{
                read(l),read(r);
                cout<<Q.query(1,1,n,l,r)%m<<endl;
            }
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
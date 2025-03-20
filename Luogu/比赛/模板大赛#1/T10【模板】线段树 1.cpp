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

int n,m;
int a[N];
struct Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node{
        int tag,sum;
    }t[N<<2];
    void pushup(int rt){
        t[rt].sum=t[lson].sum+t[rson].sum;
    }
    void build(int rt,int l,int r){
        if(l==r) {t[rt].sum=a[l],t[rt].tag=0;return;}
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
        pushup(rt);
    }
    void pushdown(int rt,int l,int r){
        if(!t[rt].tag) return;
        int mid=(l+r)>>1;
        t[lson].tag+=t[rt].tag;
        t[rson].tag+=t[rt].tag;
        t[lson].sum+=t[rt].tag*(mid-l+1);
        t[rson].sum+=t[rt].tag*(r-mid);
        t[rt].tag=0;
    }
    void update(int rt,int l,int r,int L,int R,int x){
        if(L<=l && r<=R) {t[rt].sum+=(r-l+1)*x,t[rt].tag+=x;return;}
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,x);
        if(R>mid) update(rson,mid+1,r,L,R,x);
        pushup(rt);
    }
    int query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R) return t[rt].sum;
        pushdown(rt,l,r);
        int mid=(l+r)>>1,res=0;
        if(L<=mid) res+=query(lson,l,mid,L,R);
        if(R>mid) res+=query(rson,mid+1,r,L,R);
        return res;
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) read(a[i]);
        Q.build(1,1,n);
        for(int i=1;i<=m;++i){
            int op;
            read(op);
            if(op==1){
                int l,r,k;
                read(l),read(r),read(k);
                Q.update(1,1,n,l,r,k);
            }
            else{
                int l,r;
                read(l),read(r);
                cout<<Q.query(1,1,n,l,r)<<endl;
            }
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
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

const int N=5e4+10;

int n,m;
int a[N];

struct Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node{
        int sum,lsum,rsum,msum;
    }t[N<<2];
    void pushup(int rt){
        t[rt].sum=t[lson].sum+t[rson].sum;
        t[rt].lsum=max(t[lson].lsum,t[lson].sum+t[rson].lsum);
        t[rt].rsum=max(t[rson].rsum,t[rson].sum+t[lson].rsum);
        t[rt].msum=max(t[lson].rsum+t[rson].lsum,max(t[lson].msum,t[rson].msum));
    }
    void build(int rt,int l,int r){
        if(l==r) {t[rt].sum=t[rt].lsum=t[rt].rsum=t[rt].msum=a[l];return;}
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
        pushup(rt);
    }
    void update(int rt,int l,int r,int k,int x){
        if(l==r) {t[rt].lsum=t[rt].msum=t[rt].rsum=t[rt].sum=x;return;}
        int mid=(l+r)>>1;
        if(k<=mid) update(lson,l,mid,k,x);
        else update(rson,mid+1,r,k,x);
        pushup(rt);
    }
    node query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R) return t[rt];
        int mid=(l+r)>>1;
        if(L>mid) return query(rson,mid+1,r,L,R);
        if(R<=mid) return query(lson,l,mid,L,R);
        else{
            node ans,a,b;
            a=query(lson,l,mid,L,R),b=query(rson,mid+1,r,L,R);
            ans.sum=a.sum+b.sum;
            ans.msum=max(max(a.msum,b.msum),a.rsum+b.lsum);
            ans.lsum=max(a.lsum,a.sum+b.lsum);
            ans.rsum=max(b.rsum,b.sum+a.rsum);
            return ans;
        }
    }
}Q;

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    Q.build(1,1,n);
    read(m);
    for(int i=1;i<=m;++i){
        int l,r,op;
        read(op,l,r);
        if(op==1) cout<<Q.query(1,1,n,l,r).msum<<endl;
        else Q.update(1,1,n,l,r);
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
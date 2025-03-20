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

const int N=2e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,q,A,B;
int x[N];

struct Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node{
        ll min1,min2;
        ll add;
        node(){
            min1=min2=inf;
            add=0;
        }
        void init(){
            min1=min2=inf;
            add=0;
        }
    }t[N<<2];
    void init() {for(int i=0;i<(N<<2)-1;++i) t[i].init();}
    void pushup(int rt){
        t[rt].min1=min(t[lson].min1,t[rson].min1);
        t[rt].min2=min(t[lson].min2,t[rson].min2);
    }
    void pushdown(int rt){
        if(!t[rt].add) return;
        t[lson].add+=t[rt].add;
        t[rson].add+=t[rt].add;
        t[lson].min1+=t[rt].add;
        t[rson].min1+=t[rt].add;
        t[lson].min2+=t[rt].add;
        t[rson].min2+=t[rt].add;
        t[rt].add=0;
    }
    void set(int rt,int l,int r,int k,ll val){
        if(l==r){
            t[rt].min1=min(t[rt].min1,val-l);
            t[rt].min2=min(t[rt].min2,val+l);
            return;
        }
        int mid=(l+r)>>1;
        pushdown(rt);
        if(k<=mid) set(lson,l,mid,k,val);
        else set(rson,mid+1,r,k,val);
        pushup(rt);
    }
    ll query1(int rt,int l,int r,int L,int R){
        if(L==l && r==R) return t[rt].min1;
        int mid=(l+r)>>1;
        pushdown(rt);
        if(L>mid) return query1(rson,mid+1,r,L,R);
        if(R<=mid) return query1(lson,l,mid,L,R);
        return min(query1(lson,l,mid,L,mid),query1(rson,mid+1,r,mid+1,R));
    }
    ll query2(int rt,int l,int r,int L,int R){
        if(L==l && r==R) return t[rt].min2;
        int mid=(l+r)>>1;
        pushdown(rt);
        if(L>mid) return query2(rson,mid+1,r,L,R);
        if(R<=mid) return query2(lson,l,mid,L,R);
        return min(query2(lson,l,mid,L,mid),query2(rson,mid+1,r,mid+1,R));
    }
    ll que(int rt,int l,int r){
        if(l==r) return (t[rt].min1+l);
        int mid=(l+r)>>1;
        pushdown(rt);
        return min(que(lson,l,mid),que(rson,mid+1,r));
    }
}Q;

signed main(){
    read(n),read(q),read(A),read(B);
    x[0]=A;
    Q.init();
    Q.set(1,1,n,B,0);
    for(int i=1;i<=q;++i){
        read(x[i]);
        ll tmp=min(Q.query1(1,1,n,1,x[i])+x[i],Q.query2(1,1,n,x[i],n)-x[i]);
        Q.t[1].add+=abs(x[i]-x[i-1]);
        Q.t[1].min1+=abs(x[i]-x[i-1]);
        Q.t[1].min2+=abs(x[i]-x[i-1]);
        Q.set(1,1,n,x[i-1],tmp);
    }
    cout<<Q.que(1,1,n)<<endl;
    return 0;
}
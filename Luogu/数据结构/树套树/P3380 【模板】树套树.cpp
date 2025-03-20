#include<iostream>
#include<cstdio>
#include<random>
#define int long long
#define ull unsigned long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
template<typename P>
inline void read(P &x){
    P res=0;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        res=(res<<3)+(res<<1)+ch-48;
        ch=getchar();
    }
    x=res;
}
const int Max=1e7+10,N=5e4+10;
const int inf=0x7fffffff;
int n,m;
int a[N];
struct balance{
    int val,siz,l,r,key;
}t[Max];
mt19937 rnd(233);
int tot;
#define lson (t[rt].l)
#define rson (t[rt].r)
struct FHQ_Treap{
    int root;
    int newnode(int val){
        t[++tot].val=val;
        t[tot].key=rnd();
        t[tot].siz=1;
        return tot;
    }
    void pushup(int rt){
        t[rt].siz=t[lson].siz+t[rson].siz+1;
        return;
    }
    void split(int rt,int &l,int &r,int val){
        if(!rt){
            l=r=0;
            return;
        }
        if(t[rt].val<=val){
            l=rt;
            split(rson,rson,r,val);
        }
        else{
            r=rt;
            split(lson,l,lson,val);
        }
        pushup(rt);
        return;
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        if(t[x].key>t[y].key){
            t[x].r=merge(t[x].r,y);
            pushup(x);
            return x;
        }
        else{
            t[y].l=merge(x,t[y].l);
            pushup(y);
            return y;
        }
    }
    int x,y,z;
    void ins(int val){
        split(root,x,y,val);
        root=merge(x,merge(newnode(val),y));
        return;
    }
    void del(int val){
        split(root,x,z,val);
        split(x,x,y,val-1);
        y=merge(t[y].l,t[y].r);
        root=merge(x,merge(y,z));
        return;
    }
    int grnk(int val){
        split(root,x,y,val-1);
        int res=t[x].siz+1;
        root=merge(x,y);
        return res;
    }
    void build(int l,int r){
        for(int i=l;i<=r;++i) ins(a[i]);
    }
    int gsum(int rt,int rnk){
        if(rnk<=t[lson].siz) return gsum(lson,rnk);
        if(rnk==t[lson].siz+1) return t[rt].val;
        return gsum(rson,rnk-t[lson].siz-1);
    }
    int pre(int val){
        split(root,x,y,val-1);
        int res;
        if(t[x].siz) res=gsum(x,t[x].siz);
        else res=-inf;
        root=merge(x,y);
        return res;
    }
    int nxt(int val){
        split(root,x,y,val);
        int res;
        if(t[y].siz) res=gsum(y,1);
        else res=inf;
        root=merge(x,y);
        return res;
    }
}FT[N<<2];
#define ls (rt<<1)
#define rs (rt<<1|1)
struct Stree{
    void build(int rt,int l,int r){
        FT[rt].build(l,r);
        if(l!=r){
            int mid=(l+r)>>1;
            build(ls,l,mid),build(rs,mid+1,r);
        }
        return;
    }
    int qrnk(int rt,int l,int r,int L,int R,int val){
        if(r<L || l>R) return 0;
        if(L<=l && r<=R) return FT[rt].grnk(val)-1;
        int mid=(l+r)>>1;
        return qrnk(ls,l,mid,L,R,val)+qrnk(rs,mid+1,r,L,R,val);
    }
    int qval(int l,int r,int rnk){
        int x=0,y=1e8,ans=-1;
        while(x<=y){
            int mid=(x+y)>>1;
            if(qrnk(1,1,n,l,r,mid)+1<=rnk) ans=mid,x=mid+1;
            else y=mid-1;
        }
        return ans;
    }
    void update(int rt,int l,int r,int k,int val){
        FT[rt].del(a[k]);
        FT[rt].ins(val);
        if(l!=r){
            int mid=(l+r)>>1;
            if(k<=mid) update(ls,l,mid,k,val);
            else update(rs,mid+1,r,k,val);
        }
    }
    int lower(int rt,int l,int r,int L,int R,int k){
        if(r<L || l>R) return -inf;
        if(L<=l && r<=R) return FT[rt].pre(k);
        int mid=(l+r)>>1;
        return max(lower(ls,l,mid,L,R,k),lower(rs,mid+1,r,L,R,k));
    }
    int upper(int rt,int l,int r,int L,int R,int k){
        if(r<L || l>R) return inf;
        if(L<=l && r<=R) return FT[rt].nxt(k);
        int mid=(l+r)>>1;
        return min(upper(ls,l,mid,L,R,k),upper(rs,mid+1,r,L,R,k));
    }
}ST;
signed main(){
    read(n),read(m);
    for(int i=1;i<=n;++i) read(a[i]);
    ST.build(1,1,n);
    for(int i=1;i<=m;++i){
        int opt,l,r,k,val;
        read(opt);
        if(opt==1){
            read(l),read(r),read(k);
            cout<<ST.qrnk(1,1,n,l,r,k)+1<<endl;
        }
        else if(opt==2){
            read(l),read(r),read(k);
            cout<<ST.qval(l,r,k)<<endl;
        }
        else if(opt==3){
            read(k),read(val);
            ST.update(1,1,n,k,val);
            a[k]=val;
        }
        else if(opt==4){
            read(l),read(r),read(k);
            cout<<ST.lower(1,1,n,l,r,k)<<endl;
        }
        else{
            read(l),read(r),read(k);
            cout<<ST.upper(1,1,n,l,r,k)<<endl;
        }
    }
    return 0;
}
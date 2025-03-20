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

const int N=5e4+10,Max=1e7+10,inf=0x7fffffff;

int n,m;
int a[N];
mt19937 rnd(233);
struct node{
    int l,r,siz,key,val;
}t[Max];

int cnt;
#define lson (t[rt].l)
#define rson (t[rt].r)
struct FHQ_Treap{
    int root;
    int newnode(int val){
        t[++cnt].val=val;
        t[cnt].key=rnd();
        t[cnt].siz=1;
        return cnt;
    }
    void update(int rt) {t[rt].siz=t[lson].siz+t[rson].siz+1;}
    void split(int rt,int &l,int &r,int val){
        if(!rt) {l=r=0;return;}
        if(t[rt].val<=val){
            l=rt;
            split(rson,rson,r,val);
        }
        else{
            r=rt;
            split(lson,l,lson,val);
        }
        update(rt);
        return;
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        if(t[x].key>t[y].key){
            t[x].r=merge(t[x].r,y);
            update(x);
            return x;
        }
        else{
            t[y].l=merge(x,t[y].l);
            update(y);
            return y;
        }
    }
    int x,y,z;
    void ins(int val){
        split(root,x,y,val);
        root=merge(x,merge(newnode(val),y));
        return;
    }
    void build(int l,int r) {for(int i=l;i<=r;++i) ins(a[i]);}
    void del(int val){
        split(root,x,z,val);
        split(x,x,y,val-1);
        y=merge(t[y].l,t[y].r);
        root=merge(x,merge(y,z));
    }
    int getrnk(int val){
        split(root,x,y,val-1);
        int res=t[x].siz+1;
        root=merge(x,y);
        return res;
    }
    int getval(int rt,int rnk){
        if(rnk<=t[lson].siz) return getval(lson,rnk);
        if(rnk==t[lson].siz+1) return t[rt].val;
        return getval(rson,rnk-t[lson].siz-1);
    }
    int pre(int val){
        split(root,x,y,val-1);
        int res;
        if(t[x].siz) res=getval(x,t[x].siz);
        else res=-inf;
        root=merge(x,y);
        return res;
    }
    int nxt(int val){
        split(root,x,y,val);
        int res;
        if(t[y].siz) res=getval(y,1);
        else res=inf;
        root=merge(x,y);
        return res;
    }
}F[N<<2];

#define ls (rt<<1)
#define rs (rt<<1|1)
struct Stree{
    void build(int rt,int l,int r){
        F[rt].build(l,r);
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }
    int qrnk(int rt,int l,int r,int L,int R,int val){
        if(r<L || l>R) return 0;
        if(L<=l && r<=R) return F[rt].getrnk(val)-1;
        int mid=(l+r)>>1;
        return qrnk(ls,l,mid,L,R,val)+qrnk(rs,mid+1,r,L,R,val);
    }
    int qval(int l,int r,int rnk){
        int x=0,y=1e8,ans=-1;
        while(x<=y){
            int mid=(x+y)>>1;
            if(qrnk(1,1,n,l,r,mid)+1<=rnk) x=mid+1,ans=mid;
            else y=mid-1;
        }
        return ans;
    }
    void update(int rt,int l,int r,int k,int x){
        F[rt].del(a[k]);
        F[rt].ins(x);
        if(l==r) return;
        int mid=(l+r)>>1;
        if(k<=mid) update(ls,l,mid,k,x);
        else update(rs,mid+1,r,k,x);
    }
    int qpre(int rt,int l,int r,int L,int R,int k){
        if(l>R || r<L) return -inf;
        if(L<=l && r<=R) return F[rt].pre(k);
        int mid=(l+r)>>1;
        return max(qpre(ls,l,mid,L,R,k),qpre(rs,mid+1,r,L,R,k));
    }
    int qnxt(int rt,int l,int r,int L,int R,int k){
        if(l>R || r<L) return inf;
        if(L<=l && r<=R) return F[rt].nxt(k);
        int mid=(l+r)>>1;
        return min(qnxt(ls,l,mid,L,R,k),qnxt(rs,mid+1,r,L,R,k));
    }
}Q;

inline void solve(){
    read(n,m);
    for(int i=1;i<=n;++i) read(a[i]);
    Q.build(1,1,n);
    for(int i=1;i<=m;++i){
        int op,l,r,k,val;
        read(op);
        if(op!=3) read(l,r,val);
        else read(k,val);
        if(op==1) cout<<Q.qrnk(1,1,n,l,r,val)+1<<endl;
        else if(op==2) cout<<Q.qval(l,r,val)<<endl;
        else if(op==3) Q.update(1,1,n,k,val),a[k]=val;
        else if(op==4) cout<<Q.qpre(1,1,n,l,r,val)<<endl;
        else cout<<Q.qnxt(1,1,n,l,r,val)<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
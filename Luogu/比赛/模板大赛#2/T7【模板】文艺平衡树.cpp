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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1e5+10;

int n,m;

mt19937 rnd(233);

struct FHQ_tree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int val,siz,key,l,r,rev;
    }t[N];
    int root,cnt,x,y,z;
    FHQ_tree() {root=cnt=0;}
    void pushup(int rt){
        t[rt].siz=t[lson].siz+t[rson].siz+1;
    }
    int newnode(int val){
        t[++cnt].key=rnd();
        t[cnt].siz=1;
        t[cnt].val=val;
        return cnt;
    }
    void pushdown(int rt){
        swap(lson,rson);
        t[lson].rev^=1;
        t[rson].rev^=1;
        t[rt].rev=0;
    }
    void split(int rt,int &l,int &r,int siz){
        if(!rt){
            l=r=0;
            return;
        }
        if(t[rt].rev) pushdown(rt);
        if(t[lson].siz<siz){
            l=rt;
            siz=siz-t[lson].siz-1;
            split(rson,rson,r,siz);
        }
        else{
            r=rt;
            split(lson,l,lson,siz);
        }
        pushup(rt);
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        if(t[x].key<=t[y].key){
            if(t[x].rev) pushdown(x);
            t[x].r=merge(t[x].r,y);
            pushup(x);
            return x;
        }
        else{
            if(t[y].rev) pushdown(y);
            t[y].l=merge(x,t[y].l);
            pushup(y);
            return y;
        }
    }
    void reverse(int l,int r){
        split(root,x,y,l-1);
        split(y,y,z,r-l+1);
        t[y].rev^=1;
        root=merge(merge(x,y),z);
    }
    void output(int rt){
        if(!rt) return;
        if(t[rt].rev) pushdown(rt);
        output(lson);
        cout<<t[rt].val<<' ';
        output(rson);
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) Q.root=Q.merge(Q.root,Q.newnode(i));
        for(int i=1;i<=m;++i){
            int l,r;
            read(l),read(r);
            Q.reverse(l,r);
        }
        Q.output(Q.root);
        cout<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
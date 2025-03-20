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

int n;
mt19937 rnd(time(0));

struct FHQ_tree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int val,siz,key,l,r;
    }t[N];
    int root,cnt,x,y,z;
    FHQ_tree(){
        root=0,cnt=0;
    }
    void pushup(int rt){
        t[rt].siz=t[lson].siz+t[rson].siz+1;
    }
    int newnode(int val){
        t[++cnt].val=val;
        t[cnt].siz=1;
        t[cnt].key=rnd();
        return cnt;
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
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        if(t[x].key<t[y].key){
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
    void insert(int val){
        split(root,x,y,val);
        root=merge(x,merge(newnode(val),y));
    }
    void del(int val){
        split(root,x,z,val);
        split(x,x,y,val-1);
        y=merge(t[y].l,t[y].r);
        root=merge(merge(x,y),z);
    }
    int getrnk(int val){
        split(root,x,y,val-1);
        int res=t[x].siz+1;
        root=merge(x,y);
        return res;
    }
    int getval(int rnk){
        int rt=root;
        while(rt){
            if(t[lson].siz+1==rnk) break;
            else if(t[lson].siz>=rnk) rt=lson;
            else rnk-=t[lson].siz+1,rt=rson;
        }
        return t[rt].val;
    }
    int pre(int val){
        split(root,x,y,val-1);
        int rt=x;
        while(rson) rt=rson;
        int res=t[rt].val;
        root=merge(x,y);
        return res;
    }
    int nxt(int val){
        split(root,x,y,val);
        int rt=y;
        while(lson) rt=lson;
        int res=t[rt].val;
        root=merge(x,y);
        return res;
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i){
            int op;
            int x;
            read(op);read(x);
            if(op==1) Q.insert(x);
            else if(op==2) Q.del(x);
            else if(op==3) cout<<Q.getrnk(x)<<endl;
            else if(op==4) cout<<Q.getval(x)<<endl;
            else if(op==5) cout<<Q.pre(x)<<endl;
            else cout<<Q.nxt(x)<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
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

const int N=4e6+10;
std::mt19937 rnd(233);

struct FHQ_tree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int l,r,siz,val,key;
    }t[N];
    int root,cnt;
    FHQ_tree(){root=cnt=0;}
    int newnode(int val){
        t[++cnt].key=rnd();
        t[cnt].val=val;
        t[cnt].siz=1;
        return cnt;
    }
    void update(int rt){
        t[rt].siz=t[lson].siz+t[rson].siz+1;
    }
    void split(int rt,int &l,int &r,int val){
        if(!rt){l=r=0;return;}
        if(t[rt].val<=val){
            l=rt;
            split(rson,rson,r,val);
        }
        else{
            r=rt;
            split(lson,l,lson,val);
        }
        update(rt);
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        if(t[x].key<t[y].key){
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
        root=merge(merge(x,newnode(val)),y);
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

int n,m;

signed main(){
    auto solve=[&](){
        int las=0;
        int ans=0;
        read(n),read(m);
        for(int i=1;i<=n;++i){
            int x;
            read(x);
            Q.ins(x);
        }
        for(int i=1;i<=m;++i){
            int opt,x;
            read(opt),read(x);
            x^=las;
            if(opt==1) Q.ins(x);
            else if(opt==2) Q.del(x);
            else if(opt==3) las=Q.getrnk(x),ans^=las;
            else if(opt==4) las=Q.getval(x),ans^=las;
            else if(opt==5) las=Q.pre(x),ans^=las;
            else las=Q.nxt(x),ans^=las;
        }
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
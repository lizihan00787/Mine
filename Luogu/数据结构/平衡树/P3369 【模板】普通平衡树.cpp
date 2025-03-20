#include<bits/stdc++.h>
#define int long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
std::mt19937 rnd(233);
#define lson (fhq[rt].l)
#define rson (fhq[rt].r)
const int Max=1e5+10;
struct FHQ{
    struct tree{
        int val,key,l,r,siz;
    }fhq[Max];
    int cnt,root;
    FHQ(){cnt=0,root=0;};
    int newnode(int val){
        fhq[++cnt].val=val;
        fhq[cnt].siz=1;
        fhq[cnt].key=rnd();
        return cnt;
    }
    void update(int rt){
        fhq[rt].siz=fhq[lson].siz+fhq[rson].siz+1;
    }
    void split(int rt,int &l,int &r,int val){
        if(!rt){
            l=r=0;
            return;
        }
        if(fhq[rt].val<=val){
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
        if(fhq[x].key>fhq[y].key){
            fhq[x].r=merge(fhq[x].r,y);
            update(x);
            return x;
        }
        else{
            fhq[y].l=merge(x,fhq[y].l);
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
        y=merge(fhq[y].l,fhq[y].r);
        root=merge(merge(x,y),z);
    }
    void getrank(int val){
        split(root,x,y,val-1);
        cout<<fhq[x].siz+1<<endl;
        root=merge(x,y);
    }
    void getnum(int rank){
        int rt=root;
        while(rt){
            if(fhq[lson].siz+1==rank) break;
            else if(fhq[lson].siz>=rank) rt=lson;
            else rank-=fhq[lson].siz+1,rt=rson;
        }
        cout<<fhq[rt].val<<endl;
    }
    void pre(int val){
        split(root,x,y,val-1);
        int rt=x;
        while(rson) rt=rson;
        cout<<fhq[rt].val<<endl;
        root=merge(x,y);
    }
    void nxt(int val){
        split(root,x,y,val);
        int rt=y;
        while(lson) rt=lson;
        cout<<fhq[rt].val<<endl;
        root=merge(x,y);
    }
}Q;
int n;
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i){
            int op,x;
            read(op),read(x);
            if(op==1) Q.ins(x);
            else if(op==2) Q.del(x);
            else if(op==3) Q.getrank(x);
            else if(op==4) Q.getnum(x);
            else if(op==5) Q.pre(x);
            else Q.nxt(x);
        }
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}
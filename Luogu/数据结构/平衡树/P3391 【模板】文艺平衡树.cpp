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
        bool rev;
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
    void pushdown(int rt){
        swap(lson,rson);
        fhq[lson].rev^=1;
        fhq[rson].rev^=1;
        fhq[rt].rev=0;
    }
    void split(int rt,int &l,int &r,int siz){
        if(!rt){
            l=r=0;
            return;
        }
        if(fhq[rt].rev) pushdown(rt);
        if(fhq[lson].siz<siz){
            l=rt;
            siz=siz-fhq[lson].siz-1;
            split(rson,rson,r,siz);
        }
        else{
            r=rt;
            split(lson,l,lson,siz);
        }
        update(rt);
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        if(fhq[x].key<fhq[y].key){
            if(fhq[x].rev) pushdown(x);
            fhq[x].r=merge(fhq[x].r,y);
            update(x);
            return x;
        }
        else{
            if(fhq[y].rev) pushdown(y);
            fhq[y].l=merge(x,fhq[y].l);
            update(y);
            return y;
        }
    }
    void reverse(int l,int r){
        int x,y,z;
        split(root,x,y,l-1);
        split(y,y,z,r-l+1);
        fhq[y].rev^=1;
        root=merge(merge(x,y),z);
    }
    void output(int rt){
        if(!rt) return;
        if(fhq[rt].rev) pushdown(rt);
        output(lson);
        cout<<fhq[rt].val<<' ';
        output(rson);
    }
}Q;
int n,m;
int a[100010];
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
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}
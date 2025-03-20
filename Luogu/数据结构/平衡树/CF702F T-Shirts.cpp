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

const int N=2e5+20;

mt19937 rnd(time(0));
int n,m;
int ans[N];
struct eve{
    int c,q;
}a[N];
bool cmp(eve a,eve b){
    if(a.q!=b.q) return a.q>b.q;
    return a.c<b.c;
}
int root=0,cnt=0;
struct FHQ{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int l,r,val,key;
        int cnt,minlz,cntlz;
        int id;
    }t[N];
    int newnode(int val,int idd){
        t[++cnt].val=val;
        t[cnt].id=idd;
        t[cnt].key=rnd();
        return cnt;
    }
    void pushdown(int rt){
        if(t[rt].minlz){
            if(lson) t[lson].minlz+=t[rt].minlz,t[lson].val-=t[rt].minlz;
            if(rson) t[rson].minlz+=t[rt].minlz,t[rson].val-=t[rt].minlz;
            t[rt].minlz=0;
        }
        if(t[rt].cntlz){
            if(lson) t[lson].cntlz+=t[rt].cntlz,t[lson].cnt+=t[rt].cntlz;
            if(rson) t[rson].cntlz+=t[rt].cntlz,t[rson].cnt+=t[rt].cntlz;
            t[rt].cntlz=0;
        }
    }
    void split(int rt,int &l,int &r,int val){
        if(!rt) {l=r=0;return;}
        pushdown(rt);
        if(t[rt].val<=val){
            l=rt;
            split(rson,rson,r,val);
        }
        else{
            r=rt;
            split(lson,l,lson,val);
        }
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        pushdown(x),pushdown(y);
        if(t[x].key<t[y].key){
            t[x].r=merge(t[x].r,y);
            return x;
        }
        else{
            t[y].l=merge(x,t[y].l);
            return y;
        }
    }
    void dfsins(int x,int &y,int z){
        if(!x) return;
        pushdown(x);
        dfsins(t[x].l,y,z);dfsins(t[x].r,y,z);
        t[x].l=t[x].r=0;t[x].val-=z;t[x].cnt++;
        int k1,k2;split(y,k1,k2,t[x].val),y=merge(k1,merge(x,k2));
    }
    int x,y,z;
    void ins(int val,int idd){
        split(root,x,y,val);
        root=merge(x,merge(newnode(val,idd),y));
    }
    void dfsc(int rt){
        if(!rt) return;
        pushdown(rt);
        ans[t[rt].id]=t[rt].cnt;
        dfsc(lson),dfsc(rson);
    }
}Q;

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i].c,a[i].q);
    sort(a+1,a+n+1,cmp);
    read(m);
    for(int i=1,x;i<=m;++i) read(x),Q.ins(x,i);
    for(int i=1;i<=n;++i){
        int x,y,z;
        Q.split(root,x,y,a[i].c-1);Q.split(y,y,z,a[i].c*2);
        if(z) {Q.t[z].val-=a[i].c,Q.t[z].cnt++,Q.t[z].minlz+=a[i].c,Q.t[z].cntlz++;}
        Q.dfsins(y,x,a[i].c);
        root=Q.merge(x,z);
    }
    for(int i=1;i<=m;++i) ans[Q.t[i].id]=Q.t[i].cnt;
    Q.dfsc(root);
    for(int i=1;i<=m;++i) cout<<ans[i]<<' ';
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
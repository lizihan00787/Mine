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

const int N=1e5+20;

int n,m;
int a[N];
int pre[2000010];

struct node{
    ll maxx,hismax,lazy,hislazy;
    node operator + (const node &a) const{
        node c;
        c.maxx=max(a.maxx,maxx);c.hismax=max(hismax,a.hismax);
        c.hislazy=c.lazy=0;
        return c;
    }
}t[N<<2],ans[N];
struct Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    void pushup(int rt){t[rt]=t[lson]+t[rson];}
    void pushdown(int rt){
        t[lson].hismax=max(t[lson].hismax,t[lson].maxx+t[rt].hislazy);
        t[rson].hismax=max(t[rson].hismax,t[rson].maxx+t[rt].hislazy);
        t[lson].hislazy=max(t[lson].hislazy,t[lson].lazy+t[rt].hislazy);
        t[rson].hislazy=max(t[rson].hislazy,t[rson].lazy+t[rt].hislazy);
        t[lson].maxx+=t[rt].lazy;t[rson].maxx+=t[rt].lazy;
        t[lson].lazy+=t[rt].lazy;t[rson].lazy+=t[rt].lazy;
        t[rt].hislazy=t[rt].lazy=0;
    }
    void update(int rt,int l,int r,int L,int R,ll x){
        if(L<=l && r<=R){
            t[rt].maxx+=x;t[rt].hismax=max(t[rt].hismax,t[rt].maxx);
            t[rt].lazy+=x,t[rt].hislazy=max(t[rt].hislazy,t[rt].lazy);
            return;
        }
        pushdown(rt);
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,x);
        if(R>mid) update(rson,mid+1,r,L,R,x);
        pushup(rt);
    }
    node query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R) return t[rt];
        pushdown(rt);
        int mid=(l+r)>>1;
        if(L>mid) return query(rson,mid+1,r,L,R);
        if(R<=mid) return query(lson,l,mid,L,R);
        return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
    }
}Q;

int L[N],R[N],id[N];
bool cmp(int a,int b){
    return R[a]<R[b];
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    read(m);
    for(int i=1;i<=m;++i) read(L[i],R[i]),id[i]=i;
    sort(id+1,id+m+1,cmp);
    int j=1;
    for(int i=1;i<=n;++i){
        Q.update(1,1,n,pre[a[i]+100000]+1,i,a[i]);
        pre[a[i]+100000]=i;
        while(R[id[j]]==i && j<=m) ans[id[j]]=Q.query(1,1,n,L[id[j]],R[id[j]]),j++;
    }
    for(int i=1;i<=m;++i) cout<<ans[i].hismax<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
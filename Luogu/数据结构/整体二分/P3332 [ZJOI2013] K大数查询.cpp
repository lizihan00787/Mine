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

const int N=5e4+20;

int n,m,qq;
struct opt{
    int op,l,r,id;
    ll c;
}q[N],tmp1[N],tmp2[N];
int ans[N];
struct Stree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node{
        int tag,rec;
        ll sum;
    }t[N<<2];
    void pushup(int rt){t[rt].sum=t[lson].sum+t[rson].sum;}
    void pushdown(int rt,int l,int r){
        int mid=(l+r)>>1;
        if(t[rt].rec){
            t[rt].rec=0;
            t[lson].sum=t[lson].tag=t[rson].sum=t[rson].tag=0;
            t[lson].rec=t[rson].rec=1;
        }
        if(t[rt].tag){
            t[lson].tag+=t[rt].tag;
            t[rson].tag+=t[rt].tag;
            t[lson].sum+=t[rt].tag*(mid-l+1);
            t[rson].sum+=t[rt].tag*(r-mid);
            t[rt].tag=0;
        }
    }
    void update(int rt,int l,int r,int L,int R,int val){
        if(L<=l && r<=R) {t[rt].sum+=(r-l+1)*val;t[rt].tag+=val;return;}
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,l,mid,L,R,val);
        if(R>mid) update(rson,mid+1,r,L,R,val);
        pushup(rt);
    }
    ll query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R) return t[rt].sum;
        pushdown(rt,l,r);
        int mid=(l+r)>>1;
        ll res=0;
        if(L<=mid) res+=query(lson,l,mid,L,R);
        if(R>mid) res+=query(rson,mid+1,r,L,R);
        return res;
    }
}Q;

void calc(int l,int r,int L,int R){
    if(l==r){
        for(int i=L;i<=R;++i) if(q[i].op==2) ans[q[i].id]=l;
        return;
    }
    int mid=(l+r)>>1;
    bool f1=0,f2=0;
    int s1=0,s2=0;
    Q.t[1].rec=1,Q.t[1].tag=Q.t[1].sum=0;
    for(int i=L;i<=R;++i){
        if(q[i].op==1){
            if(q[i].c>mid){
                Q.update(1,1,n,q[i].l,q[i].r,1);
                tmp2[++s2]=q[i];
            }
            else tmp1[++s1]=q[i];
        }
        else{
            ll res=Q.query(1,1,n,q[i].l,q[i].r);
            if(q[i].c>res){
                f1=1;
                q[i].c-=res;
                tmp1[++s1]=q[i];
            }
            else tmp2[++s2]=q[i],f2=1;
        }
    }
    for(int i=1;i<=s1;++i) q[i+L-1]=tmp1[i];
    for(int i=s1+1;i<=s1+s2;++i) q[i+L-1]=tmp2[i-s1];
    if(f1) calc(l,mid,L,L+s1-1);
    if(f2) calc(mid+1,r,L+s1,R);
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=m;++i){
        read(q[i].op,q[i].l,q[i].r,q[i].c);
        if(q[i].op==2) q[i].id=++qq;
    }
    calc(-n,n,1,m);
    for(int i=1;i<=qq;++i) cout<<ans[i]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
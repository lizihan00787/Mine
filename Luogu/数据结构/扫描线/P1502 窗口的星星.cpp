#include<bits/stdc++.h>
#define int long long
#define ll long long
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
#define lson (rt<<1)
#define rson (rt<<1|1)
const int Max=1e5+10;
ll n,w,h,x,y,X[Max<<1];
int cnt=0;
struct line{
    ll l,r,h;
    int flag;
    bool operator < (const line &a) const{
        return (h!=a.h)?h<a.h:flag>a.flag;
    }
}lin[Max<<2];
struct Stree{
    struct node{
        int l,r,maxx;
        int tag;
    }t[Max<<2];
    void pushup(int rt){
        t[rt].maxx=max(t[lson].maxx,t[rson].maxx);
    }
    void pushdown(int rt){
        t[lson].tag+=t[rt].tag;
        t[rson].tag+=t[rt].tag;
        t[lson].maxx+=t[rt].tag;
        t[rson].maxx+=t[rt].tag;
        t[rt].tag=0;
        return;
    }
    void build(int rt,int l,int r){
        t[rt].l=l,t[rt].r=r;
        t[rt].maxx=0;
        t[rt].tag=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(lson,l,mid);
        build(rson,mid+1,r);
    }
    void update(int rt,ll L,ll R,int v){
        int l=t[rt].l,r=t[rt].r;
        if(L<=l && r<=R){
            t[rt].tag+=v;
            t[rt].maxx+=v;
            return;
        }
        pushdown(rt);
        int mid=(l+r)>>1;
        if(L<=mid) update(lson,L,R,v);
        if(R>mid) update(rson,L,R,v);
        pushup(rt);
    }
}Q;
signed main(){
    auto solve=[&](){
        read(n);read(w),read(h);
        memset(Q.t,0,sizeof(Q.t));
        memset(lin,0,sizeof(lin));
        for(int i=1;i<=n;++i){
            int l;
            read(x),read(y);read(l);
            X[(i<<1)-1]=y;X[(i<<1)]=y+h-1;
            lin[(i<<1)-1]={y,y+h-1,x,l};
            lin[(i<<1)]={y,y+h-1,x+w-1,-l};
        }
        n=n<<1;
        sort(lin+1,lin+n+1);
        sort(X+1,X+n+1);
        int k=unique(X+1,X+n+1)-(X+1);
        for(int i=1;i<=n;++i){
            int pos1=lower_bound(X+1,X+k+1,lin[i].l)-X;
            int pos2=lower_bound(X+1,X+k+1,lin[i].r)-X;
            lin[i].l=pos1,lin[i].r=pos2;
        }
        Q.build(1,1,k);
        int ans=0;
        for(int i=1;i<=n;++i){
            Q.update(1,lin[i].l,lin[i].r,lin[i].flag);
            ans=max(ans,Q.t[1].maxx);
        }
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    read(T);
    while(T--) solve();
    return 0;
}

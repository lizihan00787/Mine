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
#define lson (rt<<1)
#define rson (rt<<1|1)
const int Max=1e6;
int n,m,cnt;
int la[Max<<2],ra[Max<<2];
int lx[Max<<2];
int ch[Max][2],dp[Max][2];
struct pos{
    int l,r,h,id;
    bool operator < (const pos &a) const{
        return h<a.h;
    }
}a[Max];
struct Stree{
    struct node{
        int tag,w;
    }t[Max<<4];
    inline void pushdown(int rt){
        t[lson].tag=t[rt].tag;
        t[rson].tag=t[rt].tag;
        t[lson].w=t[rt].tag;
        t[rson].w=t[rt].tag;
        t[rt].tag=0;
    }
    inline void update(int rt,int l,int r,int L,int R,int x){
        if(l>R || r<L) return;
        if(l>=L && r<=R){
            t[rt].tag=x;
            t[rt].w=x;
            return;
        }
        int mid=(l+r)>>1;
        if(t[rt].tag) pushdown(rt);
        update(lson,l,mid,L,R,x);
        update(rson,mid+1,r,L,R,x);
    }
    inline int query(int rt,int l,int r,int k){
        if(l>k || r<k) return 0;
        if(l==r) return t[rt].w;
        int mid=(l+r)>>1;
        if(t[rt].tag) pushdown(rt);
        return query(lson,l,mid,k)+query(rson,mid+1,r,k);
    }
}Q;
signed main(){
    auto solve=[&](){
        read(n),read(m);
        int stx,sty;
        read(stx),read(sty);
        n++;
        a[n].l=a[n].r=stx;
        a[n].h=sty,a[n].id=n;
        la[n]=stx,ra[n]=stx;
        lx[++cnt]=a[n].l;
        for(int i=1;i<n;++i){
            read(a[i].h),read(a[i].l),read(a[i].r);
            a[i].id=i;
            la[i]=a[i].l;
            ra[i]=a[i].r;
            lx[++cnt]=a[i].l;
            lx[++cnt]=a[i].r;
        }
        sort(lx+1,lx+cnt+1);
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i){
            a[i].l=lower_bound(lx+1,lx+cnt+1,a[i].l)-lx;
            a[i].r=lower_bound(lx+1,lx+cnt+1,a[i].r)-lx;
        }
        for(int i=1;i<=n;++i){
            ch[i][0]=Q.query(1,1,cnt,a[i].l);
            ch[i][1]=Q.query(1,1,cnt,a[i].r);
            Q.update(1,1,cnt,a[i].l,a[i].r,i);
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0][0]=dp[0][1]=0;
        for(int i=1;i<=n;++i){
            if(a[i].h-a[ch[i][0]].h<=m){
                if(ch[i][0]){
                    dp[i][0]=min(dp[i][0],dp[ch[i][0]][0]+la[a[i].id]-la[a[ch[i][0]].id]+a[i].h-a[ch[i][0]].h);
                    dp[i][0]=min(dp[i][0],dp[ch[i][0]][1]+ra[a[ch[i][0]].id]-la[a[i].id]+a[i].h-a[ch[i][0]].h);
                }
                else dp[i][0]=a[i].h;
            }
            if(a[i].h-a[ch[i][1]].h<=m){
                if(ch[i][1]){
                    dp[i][1]=min(dp[i][1],dp[ch[i][1]][0]+ra[a[i].id]-la[a[ch[i][1]].id]+a[i].h-a[ch[i][1]].h);
                    dp[i][1]=min(dp[i][1],dp[ch[i][1]][1]+ra[a[ch[i][1]].id]-ra[a[i].id]+a[i].h-a[ch[i][1]].h);
                }
                else dp[i][1]=a[i].h;
            }
        }
        cout<<min(dp[n][0],dp[n][1])<<endl;
    };
    io();
    //read(T);
    while(T--) solve();
    return 0;
}
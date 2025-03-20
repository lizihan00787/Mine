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

const int N=20020,inf=0x3f3f3f3f;

int n,m;
int a[N],rtt[N],id[N];
struct mx{
    int lsum,rsum,sum;
    void init(){
        lsum=rsum=-inf,sum=0;
    }
}ans;

struct Stree{
    #define lson (t[rt].ls)
    #define rson (t[rt].rs)
    #define lsum(rt) (t[rt].v.lsum)
    #define rsum(rt) (t[rt].v.rsum)
    #define sum(rt) (t[rt].v.sum)
    struct node{
        int ls,rs;
        mx v;
    }t[N<<5];
    int cnt=0;
    mx merge(mx a,mx b){
        mx c;
        c.lsum=max(a.lsum,a.sum+b.lsum);
        c.rsum=max(b.rsum,b.sum+a.rsum);
        c.sum=a.sum+b.sum;
        return c;
    }
    void build(int &rt,int l,int r){
        rt=++cnt;
        lsum(rt)=rsum(rt)=sum(rt)=r-l+1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(lson,l,mid);build(rson,mid+1,r);
    }
    void update(int &rt,int l,int r,int k){
        t[++cnt]=t[rt],rt=cnt;
        if(l==r){
            lsum(rt)=rsum(rt)=sum(rt)=-1;
            return;
        }
        int mid=(l+r)>>1;
        if(k<=mid) update(lson,l,mid,k);
        else update(rson,mid+1,r,k);
        t[rt].v=merge(t[lson].v,t[rson].v);
    }
    void query(int rt,int l,int r,int L,int R){
        if(L<=l && r<=R){
            ans=merge(ans,t[rt].v);
            return;
        }
        int mid=(l+r)>>1;
        if(L<=mid) query(lson,l,mid,L,R);
        if(R>mid) query(rson,mid+1,r,L,R);
    }
}Q;

int q[5];
int check(int x){
    int val=0;
    if(q[2]+1<=q[3]-1) ans.init(),Q.query(rtt[x],1,n,q[2]+1,q[3]-1),val+=ans.sum;
    ans.init(),Q.query(rtt[x],1,n,q[1],q[2]),val+=ans.rsum;
    ans.init(),Q.query(rtt[x],1,n,q[3],q[4]),val+=ans.lsum;
    return val>=0;
}

bool cmp(int x,int y){
    return a[x]<a[y];
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]),id[i]=i;
    sort(id+1,id+n+1,cmp);
    Q.build(rtt[1],1,n);
    Q.t[0].v.init();
    for(int i=2;i<=n;++i) rtt[i]=rtt[i-1],Q.update(rtt[i],1,n,id[i-1]);
    read(m);
    int las=0;
    for(int i=1;i<=m;++i){
        for(int j=1;j<=4;++j) read(q[j]),q[j]=(q[j]+las)%n+1;
        sort(q+1,q+5);
        int l=1,r=n;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)) las=a[id[mid]],l=mid+1;
            else r=mid-1;
        }
        cout<<las<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
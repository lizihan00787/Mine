#include<bits/stdc++.h>
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}

const int N=1e5+10;

struct operation{
    bool op;
    int l,r,k;
    int pos,t;
}q[N];
int n,m,a[N],o[N<<1],rt[N],len,tot,tmp[2][20],cnt[2];
char opt;
struct tree{
    int l,r,sum;
}t[N*400];

struct Stree{
    #define lowbit(x) ((x)&(-x))
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    
    void update(int &rt,int l,int r,int k,int val){
        if(!rt) rt=++tot;
        t[rt].sum+=val;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(k<=mid) update(lson,l,mid,k,val);
        else update(rson,mid+1,r,k,val);
    }
    void preupd(int x,int val){
        int k=lower_bound(o+1,o+len+1,a[x])-o;
        for(int i=x;i<=n;i+=lowbit(i)) update(rt[i],1,len,k,val);
    }
    int query(int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1,sum=0;
        for(int i=1;i<=cnt[1];++i) sum+=t[t[tmp[1][i]].l].sum;
        for(int i=1;i<=cnt[0];++i) sum-=t[t[tmp[0][i]].l].sum;
        if(k<=sum){
            for(int i=1;i<=cnt[1];++i) tmp[1][i]=t[tmp[1][i]].l;
            for(int i=1;i<=cnt[0];++i) tmp[0][i]=t[tmp[0][i]].l;
            return query(l,mid,k);
        }
        else{
            for(int i=1;i<=cnt[1];++i) tmp[1][i]=t[tmp[1][i]].r;
            for(int i=1;i<=cnt[0];++i) tmp[0][i]=t[tmp[0][i]].r;
            return query(mid+1,r,k-sum);
        }
    }
    int preque(int l,int r,int k){
        memset(tmp,0,sizeof(tmp));
        cnt[0]=cnt[1]=0;
        for(int i=r;i;i-=lowbit(i)) tmp[1][++cnt[1]]=rt[i];
        for(int i=l-1;i;i-=lowbit(i)) tmp[0][++cnt[0]]=rt[i];
        return query(1,len,k);
    }
}Q;
signed main(){
    read(n),read(m);
    for(int i=1;i<=n;++i) read(a[i]),o[++len]=a[i];
    for(int i=1;i<=m;++i){
        char opt;
        cin>>opt;
        q[i].op=(opt=='Q');
        if(q[i].op) read(q[i].l),read(q[i].r),read(q[i].k);
        else read(q[i].pos),read(q[i].t),o[++len]=q[i].t;
    }
    sort(o+1,o+len+1);
    len=unique(o+1,o+len+1)-o-1;
    for(int i=1;i<=n;++i) Q.preupd(i,1);
    for(int i=1;i<=m;++i){
        if(q[i].op) cout<<o[Q.preque(q[i].l,q[i].r,q[i].k)]<<endl;
        else{
            Q.preupd(q[i].pos,-1);
            a[q[i].pos]=q[i].t;
            Q.preupd(q[i].pos,1);
        }
    }
    return 0;
}
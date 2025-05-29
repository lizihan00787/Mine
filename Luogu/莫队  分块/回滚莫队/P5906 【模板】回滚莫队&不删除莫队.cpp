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

int n,m,siz;
int a[N],id[N],b[N],R[N],ans[N];
int st[N],ed[N],ed2[N];
struct que{
    int l,r,id;
}q[N];
bool cmp(que a,que b){
    return (id[a.l]==id[b.l])?a.r<b.r:id[a.l]<id[b.l];
}


void work(){
    int las=0,tmp1=0,l=0,r=0;
    for(int i=1;i<=m;++i){
        if(id[q[i].l]==id[q[i].r]){
            tmp1=0;
            for(int j=q[i].l;j<=q[i].r;++j) st[a[j]]=0;
            for(int j=q[i].l;j<=q[i].r;++j){
                if(!st[a[j]]) st[a[j]]=j;
                tmp1=max(tmp1,j-st[a[j]]);
            }
            for(int j=q[i].l;j<=q[i].r;++j) st[a[j]]=0;
            ans[q[i].id]=tmp1;continue;
        }
        int now=id[q[i].l];
        if(las!=now){
            tmp1=0;
            for(int j=l;j<=r;++j) st[a[j]]=ed[a[j]]=0;
            l=R[now];r=l-1;las=now;
        }
        int p=l,tmp2=0;
        while(r<q[i].r){
            r++;
            if(!st[a[r]]) st[a[r]]=r;
            ed[a[r]]=r;
            tmp1=max(tmp1,r-st[a[r]]);
        }
        while(p>q[i].l){
            p--;
            if(!ed2[a[p]]) ed2[a[p]]=p;
            tmp2=max(tmp2,max(ed2[a[p]],ed[a[p]])-p);
        }
        while(p<l) ed2[a[p]]=0,p++;
        ans[q[i].id]=max(tmp2,tmp1);
    }
}

inline void solve(){
    read(n);siz=sqrt(n);
    for(int i=1;i<=n;++i) id[i]=(i-1)/siz+1,read(a[i]),b[i]=a[i];
    for(int i=1;i<=id[n];++i) R[i]=(i==id[n])?n:i*siz;
    sort(b+1,b+n+1);
    int o=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+o+1,a[i])-b;
    read(m);
    for(int i=1;i<=m;++i) read(q[i].l,q[i].r),q[i].id=i;
    sort(q+1,q+m+1,cmp);
    work();
    for(int i=1;i<=m;++i) cout<<ans[i]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
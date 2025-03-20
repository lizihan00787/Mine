#include<bits/stdc++.h>
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;

const int N=5e4+20;

int n,m,l,r;
int c[N];
int id[N];
int cnt[N],ans[N];
ll lx[N],rx[N];
int sum;
struct dat{
    int l,r,sum;
}a[N];

int gcd(int a,int b){
    if(!b) return a;
    return gcd(b,a%b);
}
bool cmp(dat x,dat y){
    if(id[x.r]==id[y.r]) return x.l<y.l;
    return x.r<y.r;
}
void add(int x){
    sum-=cnt[c[x]]*(cnt[c[x]]-1)/2;
    cnt[c[x]]++;
    sum+=cnt[c[x]]*(cnt[c[x]]-1)/2;
}
void del(int x){
    sum-=cnt[c[x]]*(cnt[c[x]]-1)/2;
    cnt[c[x]]--;
    sum+=cnt[c[x]]*(cnt[c[x]]-1)/2;
}

signed main(){
    read(n),read(m);
    int siz=n/sqrt(m*2/3);
    for(int i=1;i<=n;++i) read(c[i]),id[i]=(i-1)/siz+1;
    for(int i=1;i<=m;++i){            
        read(a[i].l),read(a[i].r);
        a[i].sum=i;
        lx[i]=a[i].l,rx[i]=a[i].r;
    }
    sort(a+1,a+m+1,cmp);
    for(int i=1,l=1,r=0;i<=m;++i){
        while(l<a[i].l) del(l++);
        while(l>a[i].l) add(--l);
        while(r>a[i].r) del(r--);
        while(r<a[i].r) add(++r);
        ans[a[i].sum]=sum;
    }
    for(int i=1,x;i<=m;++i){
        x=gcd(1ll*ans[i],1ll*(rx[i]-lx[i]+1)*(rx[i]-lx[i])/2);
        if(lx[i]==rx[i]) printf("0/1\n");
        else printf("%d/%lld\n",ans[i]/x,(ll)((rx[i]-lx[i]+1)*(rx[i]-lx[i])/2)/x);
    }
    return 0;
}
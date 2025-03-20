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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=2e5+10;
const int K=448;

int n,m,l,r,siz;
int a[N],id[N];
int ans[N],cnt[N],num[520];
struct Qu{
    int l,r,id;
}q[N];

bool cmp(Qu a,Qu b){
    if(id[a.l]==id[b.l]) return a.r<b.r;
    return id[a.l]<id[b.l];
}

void add(int x){
    if(!cnt[a[x]]) num[a[x]/K]++;
    cnt[a[x]]++;
}
void del(int x){
    cnt[a[x]]--;
    if(!cnt[a[x]]) num[a[x]/K]--;
}

void query(int x){
    for(int i=1;i<=K;++i){
        if(num[i-1]!=K){
            for(int j=(i-1)*K;j<i*K;++j){
                if(!cnt[j]){
                    ans[q[x].id]=j;
                    return;
                }
            }
        }
    }
}
signed main(){
    read(n),read(m);
    siz=sqrt(n);
    for(int i=1;i<=n;++i){
        read(a[i]);
        a[i]=min(a[i],n+1);
        id[i]=(i-1)/siz+1;
    }
    for(int i=1;i<=m;++i) read(q[i].l),read(q[i].r),q[i].id=i;
    sort(q+1,q+m+1,cmp);
    l=q[1].l,r=q[1].r;
    for(int i=l;i<=r;++i) add(i);
    query(1);
    for(int i=2;i<=m;++i){
        while(l<q[i].l) del(l++);
        while(l>q[i].l) add(--l);
        while(r<q[i].r) add(++r);
        while(r>q[i].r) del(r--);
        query(i);
    }
    for(int i=1;i<=m;++i) write(ans[i]),putchar('\n');
    return 0;
}
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

const int N=250000;
const int M=1111111;

int n,m;
int cnt[M],a[N],ans[N],sum,cntq=0,cntr=0,siz;
struct dat{
    int l,r,t,id;
}qq[N];
struct change{
    int pos,val;
}qr[N];

inline bool cmp(dat a,dat b){
	return a.l/siz==b.l/siz?a.r/siz==b.r/siz?a.t<b.t:a.r<b.r:a.l<b.l;
}

inline void add(int x){
    if(!cnt[x]) ++sum;
    cnt[x]++;
}
inline void del(int x){
    cnt[x]--;
    if(!cnt[x]) --sum;
}

inline void update(int x,int t){
    if(qq[x].l<=qr[t].pos && qr[t].pos<=qq[x].r){
        del(a[qr[t].pos]);
        add(qr[t].val);
    }
    swap(a[qr[t].pos],qr[t].val);
}

signed main(){
    auto solve=[&](){
        read(n),read(m);
        siz=pow(n,0.666);
        for(int i=1;i<=n;++i) read(a[i]);
        for(int i=1;i<=m;++i){
            char opt;
            int l,r;
            cin>>opt;
            read(l),read(r);
            if(opt=='Q') qq[++cntq].l=l,qq[cntq].r=r,qq[cntq].t=cntr,qq[cntq].id=cntq;
            else qr[++cntr].pos=l,qr[cntr].val=r;
        }
        sort(qq+1,qq+cntq+1,cmp);
        int l=1,r=0,t=0;
        for(int i=1;i<=cntq;++i){
            while(l<qq[i].l) del(a[l++]);
            while(l>qq[i].l) add(a[--l]);
            while(r>qq[i].r) del(a[r--]);
            while(r<qq[i].r) add(a[++r]);
            while(t<qq[i].t) update(i,++t);
            while(t>qq[i].t) update(i,t--);
            ans[qq[i].id]=sum;
        }
        for(int i=1;i<=cntq;++i) printf("%d\n",ans[i]);
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
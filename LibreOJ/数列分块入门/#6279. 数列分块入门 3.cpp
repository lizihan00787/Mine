#include<bits/stdc++.h>
#define endl '\n'
#define int long long
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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1e5+20;

int n;
int a[N];

struct block{
    static const int M=410;
    int siz,cnt;
    int id[N],b[N];
    int L[M],R[M],kuai[M];
    void init(){
        cnt=(n-1)/(siz=sqrt(n))+1;
        memcpy(b+1,a+1,sizeof(int)*n);
        for(int i=1;i<=n;++i) id[i]=(i-1)/siz+1;
        for(int i=1;i<=cnt;++i){
            L[i]=R[i-1]+1;
            R[i]=i==cnt?n:siz*i;
            sort(b+L[i],b+R[i]+1);
        }
    }
    void add(int l,int r,int x){
        int lb=id[l],rb=id[r];
        for(int i=lb+1;i<rb;++i) kuai[i]+=x;
        for(int i=l;i<=min(r,R[lb]);++i) a[i]+=x;
        memcpy(b+L[lb],a+L[lb],sizeof(int)*(R[lb]-L[lb]+1));
        sort(b+L[lb],b+R[lb]+1);
        if(lb<rb){
            for(int i=L[rb];i<=r;++i) a[i]+=x;
            memcpy(b+L[rb],a+L[rb],sizeof(int)*(R[rb]-L[rb]+1));
            sort(b+L[rb],b+R[rb]+1);
        }
    }
    int ask(int l,int r,int x){
        int lb=id[l],rb=id[r],res=-1;
        for(int i=lb+1;i<rb;++i){
            int k=lower_bound(b+L[i],b+R[i]+1,x-kuai[i])-b-1;
            if(k>=L[i]) res=max(res,b[k]+kuai[i]);
        }
        for(int i=l;i<=min(r,R[lb]);++i) if(a[i]+kuai[lb]<x) res=max(res,a[i]+kuai[lb]);
        if(lb<rb) for(int i=L[rb];i<=r;++i) if(a[i]+kuai[rb]<x) res=max(res,a[i]+kuai[rb]);
        return res;
    }
}blk;

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) read(a[i]);
        blk.init();
        for(int i=1;i<=n;++i){
            int opt,l,r,x;
            read(opt),read(l),read(r),read(x);
            if(opt==0) blk.add(l,r,x);
            else cout<<blk.ask(l,r,x)<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
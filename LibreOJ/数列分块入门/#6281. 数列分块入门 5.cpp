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

const int N=5e4+10;

int n;
int a[N];

struct block{
    static const int M=310;
    int siz,cnt;
    int kuai[M],L[M],R[M],maxx[M];
    int id[N];
    void init(){
        cnt=(n-1)/(siz=sqrt(n))+1;
        for(int i=1;i<=cnt;++i){
            L[i]=R[i-1]+1;
            R[i]=i==cnt?n:siz*i;
            for(int j=L[i];j<=R[i];++j){
                id[j]=i;
                maxx[i]=max(maxx[i],a[j]);
                kuai[i]+=a[j];
            }
        }
    }
    void update(int l,int r){
        int lb=id[l],rb=id[r];
        for(int i=lb+1;i<rb;++i){
            if(maxx[i]<=1) continue;
            kuai[i]=0;
            maxx[i]=sqrt(maxx[i]);
            for(int j=L[i];j<=R[i];++j){
                a[j]=sqrt(a[j]);
                kuai[i]+=a[j];
            }
        }
        for(int i=l;i<=min(r,R[lb]);++i) a[i]=sqrt(a[i]);
        maxx[lb]=kuai[lb]=0;
        for(int i=L[lb];i<=R[lb];++i){
            maxx[lb]=max(maxx[lb],a[i]);
            kuai[lb]+=a[i];
        }
        if(lb<rb){
            for(int i=L[rb];i<=r;++i) a[i]=sqrt(a[i]);
            maxx[rb]=kuai[rb]=0;
            for(int i=L[rb];i<=R[rb];++i){
                maxx[rb]=max(maxx[rb],a[i]);
                kuai[rb]+=a[i];
            }
        }
    }
    int ask(int l,int r){
        int lb=id[l],rb=id[r],res=0;
        for(int i=lb+1;i<rb;++i) res+=kuai[i];
        for(int i=l;i<=min(r,R[lb]);++i) res+=a[i];
        if(lb<rb) for(int i=L[rb];i<=r;++i) res+=a[i];
        return res;
    }
}blk;

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    blk.init();
    for(int i=1;i<=n;++i){
        int opt,l,r,c;
        read(opt,l,r,c);
        if(opt==0) blk.update(l,r);
        else cout<<blk.ask(l,r)<<endl;
    }
    return;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
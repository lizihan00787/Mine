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

const int N=5e4+20,M=250;

int n,m;
int a[N],b[N];

int id[N],L[M],R[M];
int f[M][M],g[M][N];
int to[N];
int siz,cnt;

void init(){
    cnt=(n-1)/(siz=sqrt(n))+1;
    for(int i=1;i<=n;++i) id[i]=(i-1)/siz+1;
    for(int i=1;i<=cnt;++i) L[i]=R[i-1]+1,R[i]=i==cnt?n:i*siz;
    for(int i=1;i<=cnt;++i){
        int maxx=-1,maxk=0;
        memset(to,0,sizeof(to));
        for(int j=L[i];j<=n;++j){
            to[a[j]]++;
            if(to[a[j]]>maxk || (to[a[j]]==maxk && a[j]<maxx)) maxx=a[j],maxk=to[a[j]];
            if(id[j]!=id[j+1]) f[i][id[j]]=maxx;
        }
    }
    memset(to,0,sizeof(to));
    for(int i=1;i<=n;++i){
        to[a[i]]++;
        if(id[i]!=id[i+1]) for(int j=1;j<=n;++j) g[id[i]][j]=to[j];
    }
}

int query(int l,int r){
    int la=id[l],lb=id[r];
    int resk=f[la+1][lb-1],totk=g[lb-1][resk]-g[la][resk];
    memset(to,0,sizeof(to));
    to[resk]=totk;
    for(int i=l;i<=min(R[la],r);++i){
        to[a[i]]==0?(to[a[i]]=(lb>la?g[lb-1][a[i]]-g[la][a[i]]:0)+1):to[a[i]]++;
        if(to[a[i]]>totk || (to[a[i]]==totk && a[i]<resk)) resk=a[i],totk=to[a[i]];
    }
    if(lb>la)
        for(int i=L[lb];i<=r;++i){
            to[a[i]]==0?(to[a[i]]=g[lb-1][a[i]]-g[la][a[i]]+1):to[a[i]]++;
            if(to[a[i]]>totk || (to[a[i]]==totk && a[i]<resk)) resk=a[i],totk=to[a[i]];
        }
    return totk*2>(r-l+1)?resk:0;
}

inline void solve(){
    read(n,m);
    for(int i=1;i<=n;++i) read(a[i]),b[i]=a[i];
    sort(b+1,b+n+1);
    int k=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+k+1,a[i])-b;
    init();
    while(m--){
        int l,r;
        read(l,r);
        cout<<b[query(l,r)]<<endl;
    }
}

signed main(){
    // freopen("P4168_1.in","r",stdin);
    // freopen("P4168_1.ans","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
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
typedef std::complex<double> Comp;
const double pi=acos(-1);
Comp a[5000010],b[5000010];
string s;
int ans[5000010];
int n,m,limit;
void FFT(Comp *f,int flag){
    for(int i=0;i<limit;++i) if(i<ans[i]) swap(f[i],f[ans[i]]);
    for(int mid=1;mid<limit;mid<<=1){
        Comp W(cos(pi/mid),flag*sin(pi/mid));
        for(int r=mid<<1,j=0;j<limit;j+=r){
            Comp I(1,0);
            for(int l=0;l<mid;l++,I=I*W){
                Comp x=f[l+j],y=I*f[j+mid+l];
                f[j+l]=x+y,f[l+mid+j]=x-y;
            }
        }
    }
}
signed main(){
    auto solve=[&](){
        cin>>s;
        n=s.size()-1;
        for(int i=0;i<=n;++i) a[n-i]=Comp(s[i]-'0',0);
        cin>>s;
        m=s.size()-1;
        for(int i=0;i<=m;++i) b[m-i]=Comp(s[i]-'0',0);
        int k=0;
        limit=1;
        while(limit<=n+m) limit*=2,k++;
        for(int i=0;i<limit;++i) ans[i]=(ans[i>>1]>>1)|((i&1)<<(k-1));
        FFT(a,1);FFT(b,1);
        for(int i=0;i<=limit;++i) a[i]=a[i]*b[i];
        FFT(a,-1);
        memset(ans,0,sizeof(ans));
        for(int i=0;i<=n+m+1;++i) ans[i]=a[i].real()/limit+0.5;
        for(int i=0;i<=n+m;++i){
            ans[i+1]+=ans[i]/10;
            ans[i]%=10;
        }
        limit=n+m+1;
        while(ans[limit]){
            ans[limit+1]+=ans[limit]/10;
            ans[limit]%=10;
            limit++;
        }
        for(int i=limit-1;i>=0;--i) cout<<ans[i];
        cout<<endl;
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}
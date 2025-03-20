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

const int N=2e5+10,inf=0x3f3f3f3f;

int n,q;

const string ss[]={"BG","BR","BY","GR","GY","RY"};

inline void solve(){
    read(n,q);
    vector<int> a(n);
    for(int i=0;i<n;++i){
        char s[5];
        cin>>s;
        a[i]=find(ss,ss+6,s)-ss;
    }
    vector<vector<int> > lf(n),rf(n);
    for(int k=0;k<2;++k){
        vector<int> las(6,-inf);
        for(int i=0;i<n;++i){
            if(k) las[a[i]]=n-i-1,rf[n-i-1]=las;
            else las[a[i]]=i,lf[i]=las;
        }
        reverse(a.begin(),a.end());
    }
    for(int i=1;i<=q;++i){
        int x,y;
        read(x,y);
        --x,--y;
        int ans=inf;
        for(int j=0;j<6;++j){
            if(a[x]+j!=5 && j+a[y]!=5){
                ans=min(ans,abs(x-lf[x][j])+abs(lf[x][j]-y));
                ans=min(ans,abs(x-rf[x][j])+abs(rf[x][j]-y));
            }
        }
        if(ans>inf/2) ans=-1;
        cout<<ans<<endl;
    }

}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}
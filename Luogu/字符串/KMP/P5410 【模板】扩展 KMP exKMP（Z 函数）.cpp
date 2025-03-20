#include<bits/stdc++.h>
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int N=2e7+10;
string a,b;
int z[N<<1];
int n,m;
void getz(string a){
    n=a.size();
    for(int i=1,l=0,r=0;i<n;++i){
        if(i<r) z[i]=min(z[i-l],r-i);
        while(a[z[i]]==a[i+z[i]] && i+z[i]<n) z[i]++;
        if(i+z[i]>r) l=i,r=i+z[i];
    }
}
signed main(){
    auto solve=[&](){
        cin>>b>>a;
        getz(a+b);
        n=a.size();
        m=b.size();
        int ans=0;
        ans^=n+1;
        for(int i=1;i<n;++i) ans^=(min(z[i],n-i)+1)*(i+1);
        cout<<ans<<endl;
        ans=0;
        for(int i=0;i<m;++i) ans^=(min(z[i+n],n)+1)*(i+1);
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
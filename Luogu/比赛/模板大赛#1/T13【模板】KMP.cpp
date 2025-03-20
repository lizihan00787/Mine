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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=1e6+10;

int nxt[N];
char a[N],b[N];

signed main(){
    auto solve=[&](){
        scanf("%s",a+1);
        scanf("%s",b+1);
        int la=strlen(a+1),lb=strlen(b+1);
        int j=0;
        for(int i=2;i<=lb;++i){
            while(j && b[j+1]!=b[i]) j=nxt[j];
            if(b[j+1]==b[i]) j++;
            nxt[i]=j;
        }
        j=0;
        for(int i=1;i<=la;++i){
            while(j && b[j+1]!=a[i]) j=nxt[j];
            if(b[j+1]==a[i]) j++;
            if(j==lb){
                cout<<i-lb+1<<endl;
                j=nxt[j];
            }
        }
        for(int i=1;i<=lb;++i) cout<<nxt[i]<<' ';
        cout<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
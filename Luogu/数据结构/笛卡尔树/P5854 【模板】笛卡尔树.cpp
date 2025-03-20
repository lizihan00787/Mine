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

const int N=1e7+50;

int n;
int a[N];
int s[N],cnt=0;
int ls[N],rs[N];

signed main(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<=n;++i){
        int top=cnt;
        while(top && a[s[top]]>a[i]) top--;
        if(top) rs[s[top]]=i;
        if(top<cnt) ls[i]=s[top+1];
        s[cnt=++top]=i;
    }
    ll ans1=0,ans2=0;
    for(int i=1;i<=n;++i){
        ans1^=1ll*i*(ls[i]+1);
        ans2^=1ll*i*(rs[i]+1);
    }
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}
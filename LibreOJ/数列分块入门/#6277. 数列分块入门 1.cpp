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

const int N=5e4+10;

int n,siz;
int a[N];
int id[N];
int kuai[N];

void add(int l,int r,int val){
    int lb=id[l],rb=id[r];
    if(lb==rb){
        for(int i=l;i<=r;++i) a[i]+=val;
        return;
    }
    for(int i=(lb-1)*siz+1;i<=lb*siz;++i){
        a[i]+=kuai[lb];
        if(i>=l) a[i]+=val;
    }
    kuai[lb]=0;
    for(int i=(rb-1)*siz+1;i<=rb*siz;++i){
        a[i]+=kuai[rb];
        if(i<=r) a[i]+=val;
    }
    kuai[rb]=0;
    if(rb==lb+1) return;
    for(int i=lb*siz+1;i<=(rb-1)*siz;i+=siz) kuai[id[i]]+=val;
}

signed main(){
    auto solve=[&](){
        read(n);
        siz=sqrt(n);
        for(int i=1;i<=n;++i) read(a[i]),id[i]=(i-1)/siz+1;
        for(int i=1;i<=n;++i){
            int op,l,r,c;
            read(op),read(l),read(r),read(c);
            if(op==0) add(l,r,c);
            else cout<<a[r]+(kuai[id[r]])<<endl;
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}

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

// 其实感觉线段树是能写的，就是要返回一个Pair比较麻烦，注意下。

const int N=1e6+10;

int n;
int a[N];
int las[N];
int ans=0;

int lg2[N];
PII q1[N][23];
int q2[N][23];

PII query1(int l,int r){
    int k=lg2[r-l+1];
    return max(q1[l][k],q1[r-(1<<k)+1][k]);
}
int query2(int l,int r){
    int k=lg2[r-l+1];
    return max(q2[l][k],q2[r-(1<<k)+1][k]);
}


void calc(int l,int r){
    if(l>r) return;
    if(l==r){
        if(a[l]==1) ans++;
        return;
    }
    int maxs=query1(l,r).second;
    int len1=maxs-l,len2=r-maxs;
    if(len1<=len2){
        for(int i=l;i<=maxs;++i){
            int j=i+a[maxs]-1;
            if(j<maxs || j>r) continue;
            if(query2(i,j)<i) ans++;
        }
    }
    else{
        for(int j=maxs;j<=r;++j){
            int i=j-a[maxs]+1;
            if(i>maxs || i<l) continue;
            if(query2(i,j)<i) ans++;
        }
    }
    calc(l,maxs-1),calc(maxs+1,r);
}

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i){
            read(a[i]);
            q1[i][0]=mk(a[i],i);
            q2[i][0]=las[a[i]];
            las[a[i]]=i;
        }
        for(int i=2;i<=n;++i)  lg2[i]=lg2[i>>1]+1;
        for(int j=1;j<=21;++j){
            for(int i=1;i+(1<<j)-1<=n;++i){
                q1[i][j]=max(q1[i][j-1],q1[i+(1<<(j-1))][j-1]);
                q2[i][j]=max(q2[i][j-1],q2[i+(1<<(j-1))][j-1]);
            }
        }
        calc(1,n);
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
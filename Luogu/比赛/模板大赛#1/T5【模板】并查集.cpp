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

const int N=1e4+10,M=2e5+10;

int n,m;
int fa[N];
int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void unionn(int a,int b){
    int x=find(a),y=find(b);
    if(fa[y]!=x) fa[y]=x;
}

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i) fa[i]=i;
        for(int i=1;i<=m;++i){
            int op,x,y;
            read(op),read(x),read(y);
            if(op==1) unionn(x,y);
            else{
                if(find(x)==find(y)) cout<<"Y"<<endl;
                else cout<<"N"<<endl;
            }
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
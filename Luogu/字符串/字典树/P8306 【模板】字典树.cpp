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
struct node{
    int a[72];
    int flag;
}t[3000010];
string a;
int n,m;
int u,cnt=0;
int get(char a){
    if(a>='A' && a<='Z') return (int)(a-'A');
    else if(a>='a' && a<='z') return (int)(a-'a'+26);
    else return (int)(a-'0'+52);
}
void insert(string s){
    int len=s.size();
    u=0;
    s='0'+s;
    for(int i=1;i<=len;++i){
        int k=get(s[i]);
        if(!t[u].a[k]) t[u].a[k]=++cnt;
        u=t[u].a[k];
        t[u].flag++;
    }
}
int query(string s){
    int len=s.size();
    u=0;
    s='0'+s;
    for(int i=1;i<=len;++i){
        int k=get(s[i]);
        if(!t[u].a[k]) return 0;
        u=t[u].a[k];
    }
    return t[u].flag;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=0;i<=cnt;++i) for(int j=0;j<=70;++j) t[i].a[j]=0;
        for(int i=0;i<=cnt;++i) t[i].flag=0;
        cnt=0;
        for(int i=1;i<=n;++i){
            cin>>a;
            insert(a);
        }
        for(int i=1;i<=m;++i){
            cin>>a;
            cout<<query(a)<<endl;
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    read(T);
    while(T--) solve();
    return 0;
}
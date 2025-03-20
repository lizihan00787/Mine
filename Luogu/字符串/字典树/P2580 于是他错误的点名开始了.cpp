#include<bits/stdc++.h>
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
    int a[27];
    bool flag;
    int p;
    node(){
        flag=0;
        memset(a,0,sizeof(a));
        p=0;
    }
}t[800000];
string a;
int n,m;
int u,cnt=0;
int get(char a){
    return (int)(a-'a');
}
void insert(string s){
    int len=s.size();
    u=0;
    s='0'+s;
    for(int i=1;i<=len;++i){
        int k=get(s[i]);
        if(!t[u].a[k]) t[u].a[k]=++cnt;
        u=t[u].a[k];
    }
    t[u].flag=1;
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
    if(!t[u].flag) return 0;
    if(!t[u].p){
        t[u].p++;
        return 1;
    }
    return 2;
}
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i){
            cin>>a;
            insert(a);
        }
        read(m);
        for(int i=1;i<=m;++i){
            cin>>a;
            int q=query(a);
            if(q==0) cout<<"WRONG"<<endl;
            else if(q==1) cout<<"OK"<<endl;
            else if(q==2) cout<<"REPEAT"<<endl;
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    // read(T);
    while(T--) solve();
    return 0;
}
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
    int a[27];
    int num;
    node(){
        memset(a,0,sizeof(a));
        num=0;
    }
}trie[500010];
int n;
string t;
string s;
int u,cnt=0;
int fail[500010];
int get(char a) {return (int)(a-'a');}
void insert(string s){
    int len=s.size();
    s='0'+s;
    u=0;
    for(int i=1;i<=len;++i){
        int k=get(s[i]);
        if(!trie[u].a[k]) trie[u].a[k]=++cnt;
        u=trie[u].a[k];
    }
    trie[u].num++;
}
void build(){
    queue<int> q;
    for(int i=0;i<26;++i) if(trie[0].a[i]) q.push(trie[0].a[i]);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;++i){
            int v=trie[u].a[i];
            if(v) fail[v]=trie[fail[u]].a[i],q.push(v);
            else trie[u].a[i]=trie[fail[u]].a[i];
        }
    }
}
int query(string s){
    int len=s.size();
    s='0'+s;
    u=0;
    int ans=0;
    for(int k=1,i=0;k<=len;++k){  
        int p=get(s[k]);
        i=trie[i].a[p];
        for(int j=i;j && ~trie[j].num;j=fail[j]){
            ans+=trie[j].num;
            trie[j].num=-1;
        }
    }
    return ans;
}
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) cin>>t,insert(t);
        build();
        cin>>s;
        cout<<query(s)<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}
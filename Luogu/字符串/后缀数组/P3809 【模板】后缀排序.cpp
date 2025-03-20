#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
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
const int N=2e6+10;
char s[N];
int n,m;
int x[N],y[N],sa[N],rk[N],h[N];
int c[N];
void getsa(){
    int i,k;
    for(i=1;i<=n;++i) c[x[i]=s[i]]++;
    for(i=1;i<=m;++i) c[i]+=c[i-1];
    for(i=n;i>=1;--i) sa[c[x[i]]--]=i;
    for(k=1;k<=n;k<<=1){
        //第二关键字排序
        memset(c,0,sizeof(c));
        for(i=1;i<=n;++i) y[i]=sa[i];
        for(i=1;i<=n;++i) c[x[y[i]+k]]++;
        for(i=1;i<=m;++i) c[i]+=c[i-1];
        for(i=n;i>=1;--i) sa[c[x[y[i]+k]]--]=y[i];
        //第一关键字排序
        memset(c,0,sizeof(c));
        for(i=1;i<=n;++i) y[i]=sa[i];
        for(i=1;i<=n;++i) c[x[y[i]]]++;
        for(i=1;i<=m;++i) c[i]+=c[i-1];
        for(i=n;i>=1;--i) sa[c[x[y[i]]]--]=y[i];
        //重排
        for(i=1;i<=n;++i) y[i]=x[i];
        for(m=0,i=1;i<=n;++i){
            if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=m;
            else x[sa[i]]=++m;
            if(m==n) break;
        }
    } 
}
void geth(){
    for(int i=1;i<=n;++i) rk[sa[i]]=i;
    for(int i=1,k=0;i<=n;++i){
        if(rk[i]==1) continue;
        if(k) k--;
        int j=sa[rk[i]-1];
        while(i+k<=n && j+k<=n && s[i+k]==s[j+k]) k++;
        h[rk[i]]=k;
    }
}
signed main(){
    scanf("%s",s+1);
    n=strlen(s+1);m=122;
    getsa();
    // geth();
    for(int i=1;i<=n;++i) printf("%d ",sa[i]);
    printf("\n");
    return 0;
}
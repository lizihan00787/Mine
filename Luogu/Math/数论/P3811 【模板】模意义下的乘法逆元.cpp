#include<bits/stdc++.h>
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
int n,mod;
int inv[3000010];
int main(){
    read(n),read(mod);
    inv[1]=1;
    puts("1");
    for(int i=2;i<=n;++i){
        inv[i]=(long long)(mod-mod/i)*inv[mod%i]%mod;
        printf("%d\n",inv[i]);
    }
    return 0;
}
#include<bits/stdc++.h>
#define endl '\n'
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

const int N=2e5+10;

int n;
char s[N];
int a[N];
int lol[N],lor[N],num1,num2,ans,len;


int findl(int loc) {
	int l=0,r=num1+1;
    int ans=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(lol[mid]>=loc) r=mid-1;
		else l=mid+1,ans=mid;
	}
	return lol[ans];
}
int findr(int loc) {
	int l=0,r=num2+1;
    int ans=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(lor[mid]<loc) l=mid+1;
		else r=mid-1,ans=mid;
	}
	return lor[ans];
}

signed main(){
    auto solve=[&](){
        read(n);
        scanf("%s",s+1);
        num1=num2=ans=len=0;
        for(int i=1;i<=n;++i){
            if(s[i]=='=') ++len;
            else ans-=(len+1)*len,len=0;
            if(s[i]=='<') lol[++num1]=i;
            if(s[i]=='>') lor[++num2]=i;
        }
        lol[num1+1]=lor[num2+1]=0x3f3f3f3f;
        for(int i=1;i<=n;++i){
            int lc=findl(i),rc=findr(i);
            if(lc==0) ans+=i-1;
            else ans+=i-lc-1;
            if(rc==0x3f3f3f3f) ans+=n-i;
            else ans+=rc-i;
        }
        cout<<ans<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}
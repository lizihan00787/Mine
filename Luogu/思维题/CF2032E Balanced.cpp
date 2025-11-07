#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
using namespace std;
template<typename P>
void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
	     if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename PP,typename ...Arc>
void read(PP &x,Arc &...y) {read(x),read(y...);}
int T=1;

const int N=2e5+20;

int n,sum;
int a[N],b[N],c[N];

int chk(int x){
	return (x>n)?x-n:x;
}

void solve(){
	sum=0;
    read(n);
	for(int i=1;i<=n;++i) read(a[i]),b[i]=c[i]=0;
	if(n==1) {puts("0");return;}
	for(int i=chk(3),j=1;i!=1;j=i,i=chk(i+2)) b[i]=b[j]+(a[chk(j+1)]-a[i]);
	if(b[n-1]+a[n]-a[1]) {puts("-1");return;}
	for(int i=1;i<=n;++i) sum+=b[i];
	if(sum&1) for(int i=1;i<=n;++i) b[i]++,sum++;
	sum>>=1;
	for(int i=2;i<=n;i+=2) sum-=b[i];
	c[1]=sum;
	for(int i=2;i<=n;++i) c[i]=b[i-1]-c[i-1];
	sum=*min_element(c+1,c+n+1);
	for(int i=1;i<=n;++i) cout<<c[i]-sum<<' ';
	cout<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(T);
    while(T--) solve();
    return 0;
}



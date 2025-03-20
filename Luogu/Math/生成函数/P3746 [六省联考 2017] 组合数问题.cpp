#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
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

int p,k;
vector<int> operator * (const vector<int> &l,const vector<int> &r){
	vector<int> res(k);
	for(int i=0;i<k;++i)
		for(int j=0;j<k;++j)
			res[(i+j)%k]=(res[(i+j)%k]+1ll*l[i]*r[j])%p;
	return res;
}

void solve(){
    int n,r;
	read(n,p,k,r);
	vector<int> a(k),ans(k);
	if(k==1) a[0]=2%p;
	else a[0]=a[1]=1;
	ans[0]=1;
	auto e=1ll*n*k;
	while(e>0){
		if(e&1) ans=ans*a;
		a=a*a;
		e>>=1;
	}
	cout<<ans[r]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



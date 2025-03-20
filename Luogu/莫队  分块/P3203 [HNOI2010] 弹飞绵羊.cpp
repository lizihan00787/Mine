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

const int N=1e6+20;

int n,m;
int a[N];

struct blk{
	int cnt,siz;
	int id[N],jump[N],step[N];
	int L[N],R[N];
	void update(int l,int r){
		for(int i=r;i>=l;--i){
			if(i+a[i]>R[id[i]]){
				jump[i]=i+a[i];
				step[i]=1;
			}
			else{
				jump[i]=jump[i+a[i]];
				step[i]=step[i+a[i]]+1;
			}
		}
	}
	void init(){
		cnt=(n-1)/(siz=sqrt(n))+1;
		for(int i=1;i<=n;++i) id[i]=(i-1)/siz+1;
		for(int i=1;i<=cnt;++i){
			L[i]=R[i-1]+1;
			R[i]=i==cnt?n:i*siz;
		}
		update(1,n);
	}
	int ask(int x){
		int ans=0;
		while(x<=n){
			ans+=step[x];
			x=jump[x];
		}
		return ans;
	}
	void modify(int x){
		update(L[id[x]],R[id[x]]);
	}
}Q;

void solve(){
    read(n);
	for(int i=1;i<=n;++i) read(a[i]);
	Q.init();
	read(m);
	for(int i=1;i<=m;++i){
		int op,x,k;
		read(op,x);
		x++;
		if(op==1) cout<<Q.ask(x)<<endl;
		else{
			read(k);
			a[x]=k;
			Q.modify(x);
		}
	}
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}



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

const int N=1e6+100;


ll a[N],b[N];

struct SA{
	int n,m;
    int st[N][25],lg2[N];
	int sa[N],rk[N],cnt[150],height[N];
	char S[N];
	struct node {
		int id, x, y; 
	}aa[N], bb[N];
	inline void buildsa() {
		n = strlen(S + 1);
		memset(cnt, 0, sizeof(cnt)); 
		memset(height, 0, sizeof(height));
		memset(sa, 0, sizeof(sa));
		memset(rk, 0, sizeof(rk)); 
		for(int i = 1; i <= n; i++) aa[i].id = bb[i].id = aa[i].x = aa[i].y = bb[i].x = bb[i].y = 0; 
		for(int i = 1; i <= n; i++) cnt[S[i]] = 1; 
		for(int i = 1; i <= 256; i++) cnt[i] += cnt[i - 1];
		for(int i = 1; i <= n; i++) rk[i] = cnt[S[i]];
		for(int L = 1; L < n; L *= 2) {
			for(int i = 1; i <= n; i++) aa[i].id = i, aa[i].x = rk[i], aa[i].y = rk[i + L]; 
			for(int i = 1; i <= n; i++) cnt[i] = 0;
			for(int i = 1; i <= n; i++) cnt[aa[i].y]++;
			for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
			for(int i = n; i >= 1; i--) bb[cnt[aa[i].y]--] = aa[i];
			for(int i = 1; i <= n; i++) cnt[i] = 0;
			for(int i = 1; i <= n; i++) cnt[aa[i].x]++;
			for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
			for(int i = n; i >= 1; i--) aa[cnt[bb[i].x]--] = bb[i];
			for(int i = 1; i <= n; i++) 
				if(aa[i].x == aa[i - 1].x && aa[i].y == aa[i - 1].y)
					rk[aa[i].id] = rk[aa[i - 1].id];
				else rk[aa[i].id] = rk[aa[i - 1].id] + 1; 
    }
	for(int i = 1; i <= n; i++) sa[rk[i]] = i; int k = 0; 
    for(int i = 1; i <= n; i++) {
      if(k) k--;
      int j = sa[rk[i] - 1];
      while(i + k <= n && j + k <= n && S[i + k] == S[j + k]) k++;
      height[rk[i]] = k;
    }
  }
	void init(){
		lg2[0]=-1;
		for(int i=1;i<N;++i) lg2[i]=lg2[i/2]+1;
		lg2[0]=0;
		for(int i=1;i<=n;++i) st[i][0]=height[i];
		for(int j=1;(1<<j)<=n;++j){
			for(int i=1;i+(1<<j)-1<=n;++i){
				st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
			}
		}
	}
	int lcp(int l,int r){
		l=rk[l],r=rk[r];
		if(l>r) swap(l,r);
		l++;
		int k=lg2[r-l+1];
		return min(st[l][k],st[r-(1<<k)+1][k]);
	}
}SA[2];

void solve(){
    scanf("%s",SA[0].S+1);
	int n=strlen(SA[0].S+1);
	for(int i=1;i<=n;++i) a[i]=b[i]=0;
	for(int i=1;i<=n;++i) SA[1].S[i]=SA[0].S[n-i+1];
	SA[0].buildsa(),SA[1].buildsa();
	SA[0].init(),SA[1].init();
	for(int len=1;len<=n/2;++len){
		for(int i=len;i<=n;i+=len){
			int l=i,r=i+len;
			int L=n-(r-1)+1,R=n-(l-1)+1;
			int lp=SA[0].lcp(l,r);lp=min(lp,len);
			int ls=SA[1].lcp(L,R);ls=min(ls,len-1);
			if(lp+ls>=len){
				b[i-ls]++,b[i-ls+(lp+ls-len+1)]--;
				a[r+lp-(lp+ls-len+1)]++,a[r+lp]--;
			}
		}
	}
	for(int i=1;i<=n;++i) a[i]+=a[i-1],b[i]+=b[i-1];
	ll ans=0;
	for(int i=1;i<n;++i) ans+=a[i]*b[i+1];
	cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(T);
    while(T--) solve();
    return 0;
}



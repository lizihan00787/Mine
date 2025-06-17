#include<bits/stdc++.h>

using namespace std;

constexpr int maxn=2000006,mo=1e9+7;

using i64=long long;

int T;

int n,m,a[maxn],pos[maxn];

int l1[maxn],r1[maxn],l2[maxn],r2[maxn],f1[maxn],f2[maxn],sum[maxn];

inline int add(int x,int y){
	x+=y;return x<mo?x:x-mo;
}

inline void upd(int &x,int y){
	x=add(x,y);return;
}

int fac[maxn],ifac[maxn];

int ksm(int x,int y){
	int rs=1;for(;y;y>>=1,x=(i64)x*x%mo) if(y&1) rs=(i64)rs*x%mo;return rs;
}

void prework(){
	fac[0]=1;for(int i=1;i<maxn;++i) fac[i]=(i64)fac[i-1]*i%mo;
	ifac[maxn-1]=ksm(fac[maxn-1],mo-2);
	for(int i=maxn-1;i;--i) ifac[i-1]=(i64)ifac[i]*i%mo;
}

inline int C(int x,int y){
	if(x<y||y<0) return 0;
	return (i64)fac[x]*ifac[y]%mo*ifac[x-y]%mo;
}

inline int S(int l,int r){
	l=max(l,0);r=min(r,n-2);
	if(l>r) return 0;
	return add(sum[r],(l?mo-sum[l-1]:0));
}

inline bool chk(int x,int y){
	if(x<=y) return x+y<=n+1;
	return x+y>n+1;
}

inline int get(int l,int r,int x,int y){
	return add(add(C(l+r,l),mo-C(l+r,x-1+r)),mo-C(l+r,y+1+r));
}

inline int path(int l1,int r1,int l2,int r2){
	int l=(l1-l2+n)%n,r=(r2-r1+n)%n;
	
	if((l+r>=n)||(!chk(l2,r2))) return 0;
	else if(l1<=r1) return get(l,r,l1+r1-n-1,l1+r1-2);
	else return get(l,r,-n,l1+r1-n-2);
}

void clean(){
	m=0;
	for(int i=1;i<=n;++i) pos[i]=0;
}

int sol(){
	clean();

	for(int i=1;i<=n;++i) if(a[i]>0) pos[a[i]]=((i&1)?((i+1)>>1):n-i/2+1);
	
	for(int i=1;i<=n;++i){
		if(!pos[i]) continue;
		
		++m;
		if(i==1){
			l1[m]=r1[m]=l2[m]=r2[m]=pos[i];f1[m]=1;f2[m]=0;
		}
		else{
			l1[m]=pos[i]%n+1;r1[m]=(pos[i]+i-2)%n+1;
			l2[m]=(pos[i]+n-i)%n+1;r2[m]=(pos[i]+n-2)%n+1;
			f1[m]=f2[m]=0;
			
			if(m==1){
				for(int j=1;j<=((n+1)>>1);++j){
					upd(f1[m],path(j,j,l1[m],r1[m]));upd(f2[m],path(j,j,l2[m],r2[m]));
				}
			}
			else{
				upd(f1[m],(i64)f1[m-1]*path(l1[m-1],r1[m-1],l1[m],r1[m])%mo);
				upd(f1[m],(i64)f2[m-1]*path(l2[m-1],r2[m-1],l1[m],r1[m])%mo);
				upd(f2[m],(i64)f1[m-1]*path(l1[m-1],r1[m-1],l2[m],r2[m])%mo);
				upd(f2[m],(i64)f2[m-1]*path(l2[m-1],r2[m-1],l2[m],r2[m])%mo);
			}
			
			l1[m]=r2[m]=pos[i];
		}
		
		if(i<n){
			if(!chk(l1[m],r1[m])) f1[m]=0;
			if(!chk(l2[m],r2[m])) f2[m]=0;
		}	
	}
	
	if(pos[n]) return f1[m];
	if(m){
		int res=0;
		for(int i=((n+1)>>1)+1;i<=n;++i){
			upd(res,(i64)f1[m]*path(l1[m],r1[m],i%n+1,(i+n-2)%n+1)%mo);
			upd(res,(i64)f2[m]*path(l2[m],r2[m],i%n+1,(i+n-2)%n+1)%mo);
		}
		return res;
	}
	
	int res=0;
	
	sum[0]=1;
	for(int i=1;i<=n-2;++i) sum[i]=add(sum[i-1],C(n-2,i));
	
	for(int i=1;i<=((n+1)>>1);++i) res=add(res,add(S(((n+1)>>1)-i,n-i-1),add(mo-S(i-n/2-2,i-3),mo-S(i+((n+1)>>1)-1,i+n-2))));
	
	return res;
}

int ans;

void solve(){
	ans=0;
	cin>>n;for(int i=1;i<=n;++i) cin>>a[i];
	upd(ans,sol());
	
	for(int i=1;i<=n;++i) if(a[i]>0) a[i]=n-a[i]+1;
	upd(ans,sol());
	
	cout<<ans<<'\n';
}

int main(){
	// freopen("cat6.in","r",stdin);
	// freopen("cat6.ans","w",stdout);
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	
	prework();
	
	cin>>T;while(T--) solve();
	
	return 0;
}

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
#define maxn 1000020
#define maxn1 100000
using namespace std;
int T=1;
int a[maxn],s[maxn1],idx,n,p[maxn1],ans;
void p_s(){
	memset(a,1,sizeof(a));
	a[1]=0;
	for(int i=2;i<=maxn;i++){
		if(a[i]) s[++idx]=i,p[idx]=1ll*s[idx]*s[idx];
		for(int j=1;j<=idx&&i*s[j]<=maxn;j++){
			a[i*s[j]]=0;
			if(i%s[j]==0) break;
		}
	}
}
signed main(){
	auto solve=[&](){
		p_s();
		cin>>n;
        int ans=0;
        for(int i=1;i<=idx;i++){
			if(p[i]*s[i+1]*p[i+2]>n) break;
			for(int j=i+1;j<=idx;j++){
				if(p[i]*s[j]*p[j+1]>n) break;
				for(int k=j+1;k<=idx;k++){
					if(p[i]*s[j]*p[k]<=n) ans++;
					else break;
				}
			}
		}
        cout<<ans<<endl;
	};
	io();
	while(T--) solve();
	return 0;
}



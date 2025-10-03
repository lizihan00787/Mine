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
using namespace std;
const int mod=998244353;
int T=1;
int Q;
queue<int> q;
signed main(){
//	auto work=[&](){
//		int len=q.size();
//		int ans=0;
//		while(!q.empty()){
//			int pre=q.front();
//			q.pop();
//			ans+=pow(10,len-1)*pre;
//			len--;
//		}
//		return ans;
//	};
	auto solve=[&](){
		cin>>Q;
		q.push(1);
		int ans=1;
		int len=1;
		while(Q--){
			int op;
			cin>>op;
			if(op==1){
				int x;
				cin>>x;
				q.push(x);
				ans*=10;
				ans+=x;
				ans%=mod;
				len++;
			}
			else if(op==2){
				ans-=(int)(pow(10,len-1))*q.front();
				q.pop();
				len--;
			}
			else{
				cout<<ans%mod<<endl;
			}
		}	
	};
	io();

	while(T--) solve();
	return 0;
}


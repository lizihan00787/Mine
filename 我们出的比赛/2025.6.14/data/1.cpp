#include <bits/stdc++.h>
using namespace std;
const int N=1e6;
int t,sum,ns[N+10],sz[N+10];
mt19937 rnd(time(0));
int main()
{
	freopen("cat8.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		int n;cin>>n;sum+=n; 
		for(int i=1,x;i<=n;i++)cin>>x;
	}
	cout<<sum<<'\n';
	return 0;
} 

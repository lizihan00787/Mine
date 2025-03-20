#include<bits/stdc++.h>
#define mk(a,b) make_pair(a,b)
#define int long long
#define int128 __int128
#define ll long long
#define sc(a) scanf("%d",&(a))
#define lsc(a) scanf("%lld",&(a))
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define R(i,a,b) for(int i=(a);i>=(b);--i)
#define endl "\n"
using namespace std;
signed main() {
    int n,m;
    cin>>n>>m;
    int l=1,r=n,x=-1;
    while(l<=r)
	{
        int mid=(l+r)>>1;
        if((mid*mid)>=m && (mid*mid)<=n*n)
		{
            x=mid*mid;
            break;
        }
		else if((mid*mid)<m)
		{
            l=mid+1;
        }
		else
		{
            r=mid-1;
        }
    }
    
    cout<<x<<endl;
    return 0;
}

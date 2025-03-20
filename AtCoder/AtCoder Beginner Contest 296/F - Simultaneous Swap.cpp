#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    set<pair<vector<int>,vector<int> > > s;
    s.insert({a,b});
    queue<pair<vector<int>,vector<int> > > q;
    q.push({a,b});
    while(!q.empty())
	{
        auto x=q.front().first,y=q.front().second;
        q.pop();
        for(int i=0;i<n;i++)
		{
            for(int j=0;j<n;j++)
			{
                for(int k=0;k<n;k++)
				{
                    if(i==j || j==k || k==i) continue;
                    vector<int> nx=x,ny=y;
                    swap(nx[i],nx[j]);
                    swap(ny[i],ny[k]);
                    if(s.count({nx,ny})) continue;
                    s.insert({nx,ny});
                    q.push({nx,ny});
                }
            }
        }
    }
    if(s.count({b, a})) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}

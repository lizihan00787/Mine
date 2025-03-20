#include<bits/stdc++.h>
// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
#define int long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
int n,m;
char pp[7]="snuke";
char mapp[520][520];
const int xx[4]={1,0,-1,0};
const int yy[4]={0,1,0,-1};
bool vis[520][520];
struct node{
    int x,y,s;
};
queue<node> q;
signed main(){
    auto check=[&](int x,int y){
        if(x>=1 && x<=n && y>=1 && y<=m && !vis[x][y]) return 1;
        return 0;
    };
    auto bfs=[&](){
        while(!q.empty()){
            auto it=q.front();
            q.pop();
            int X=it.x;
            int Y=it.y;
            int S=it.s;
            int L=(S+5)%5;
            if(X==n && Y==m){
                cout<<"Yes"<<endl;
                exit(0);
            }
            for(int i=0;i<=3;++i){
                int nx=X+xx[i];
                int ny=Y+yy[i];
                if(check(nx,ny) && mapp[nx][ny]==pp[(L+1+5)%5]){
                    q.push(node{nx,ny,L+1});
                    vis[nx][ny]=1;
                }
            }
        }
    };
    auto solve=[&](){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                cin>>mapp[i][j];
            }
        }
        if(mapp[1][1]!='s'){
            cout<<"No"<<endl;
            return;
        }
        vis[1][1]=1;
        q.push(node{1,1,0});
        bfs();
        cout<<"No"<<endl;
    };
    io();
    //cin>>T;
    while(T--) solve();
    return 0;
}
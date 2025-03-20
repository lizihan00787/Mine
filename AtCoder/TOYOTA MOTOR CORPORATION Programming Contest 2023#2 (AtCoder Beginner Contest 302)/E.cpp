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
#define mk(a,b) make_pair(a,b)
#define pbds __gnu_pbds::
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
using namespace std;
int T=1;
const int MAXN = 3e5 + 5;

int N, Q;
int parent[MAXN], size[MAXN];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (size[u] < size[v]) swap(u, v);
    parent[v] = u;
    size[u] += size[v];
}
signed main(){
	auto solve=[&](){
		cin >> N >> Q;
	    for (int i = 1; i <= N; i++) {
	        parent[i] = i;
	        size[i] = 1;
	    }
	    int components = N;
	    while (Q--) {
	        int type, u, v;
	        cin >> type >> v;
	        if (type == 1) {
	            cin >> u;
	            merge(u, v);
	            components--;
	        } else {
	            for (int i = 1; i <= N; i++) {
	                if (find(i) == find(v) && i != v) {
	                    size[find(i)]--;
	                    parent[i] = i;
	                    components++;
	                }
	            }
	        }
	        cout << components << "\n";
	    }
	};
	io();

	while(T--) solve();
	return 0;
}



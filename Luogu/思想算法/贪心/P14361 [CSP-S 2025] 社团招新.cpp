#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
using namespace std;
template <typename P>
inline void read(P &x) {
    P res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = (res << 3) + (res << 1) + (ch ^ 48);
        ch = getchar();
    }
    x = res * f;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) { read(x); read(args...); }
int T = 1;

const int N = 1e5 + 10;

int n;

inline void solve() {
    read(n);
    int ans = 0;
    priority_queue<int, vector<int>, less<int> > q1, q2, q3;
    for (int i = 1; i <= n; ++i) {
        int x, y, z;
        read(x, y, z);
        int p = max(x, max(y, z));
        ans += p;
        if (p == x) q1.push(max(y - x, z - x));
        else if(p == y) q2.push(max(x - y, z - y));
        else q3.push(max(x - z, y - z));
    }
    while (q1.size() > n / 2) ans += q1.top(), q1.pop();
    while (q2.size() > n / 2) ans += q2.top(), q2.pop();
    while (q3.size() > n / 2) ans += q3.top(), q3.pop();
    printf("%d\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}
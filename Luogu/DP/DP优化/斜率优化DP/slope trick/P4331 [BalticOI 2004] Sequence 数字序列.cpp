#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define ull unsigned long long
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
inline void read(Ty &x, Args &...args) {read(x); read(args...);}
int T = 1;

const int N = 1e6 + 20;

int n, ans, a[N], b[N];
priority_queue<int, vector<int>, less<int> > q;

inline void solve() {
    read(n);
    read(b[1]); b[1]--, q.push(b[1]);
    a[1] = q.top();
    for (int i = 2; i <= n; ++i) {
        read(b[i]); b[i] -= i;
        q.push(b[i]);
        if (b[i] < q.top()) {
            ans += q.top() - b[i];
            q.pop(); q.push(b[i]);
        }
        a[i] = q.top();
    }
    for (int i = n - 1; i >= 1; --i) a[i] = min(a[i], a[i + 1]);
    ll res = 0;
    for (int i = 1; i <= n; ++i) res += abs(a[i] - b[i]);
    cout << res << endl;
    for (int i = 1; i <= n; ++i) cout << a[i] + i << ' ';
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
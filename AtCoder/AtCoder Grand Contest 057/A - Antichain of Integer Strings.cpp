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

int get(int x) {
    if (x < 10) return 0;
    int y = 1;
    while (x > 9) {
        x /= 10;
        y *= 10;
    }
    return y;
}
int l, r;
int p[10];

inline void solve() {
    read(l, r);
    p[1] = 1;
    for (int i = 2; i <= 9; ++i) p[i] = p[i - 1] * 10;
    int ls = get(l), rs = get(r);
    if (ls == rs) return (void)(printf("%d\n", r - l + 1));
    int cnt = r - rs + 1;
    int app = rs - max(max(l, r / 10 + 1), cnt);
    printf("%d\n", cnt + max(app, 0));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}
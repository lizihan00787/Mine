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
inline void read(Ty &x, Args &...args) {
    read(x);
    read(args...);
}
int T = 1;

const int N = 1510;

int n, cnt, fail;

ll ans;
struct point {
    ll x, y;
} a[N];
struct line {
    ll x1, x2, y1, y2, midx, midy, len;
    bool operator<(const line &a) const {
        if (midx == a.midx) {
            if (midy == a.midy) return len < a.len;
            return midy < a.midy;
        }
        return midx < a.midx;
    }
} l[N * N];

ll dis(int x1, int y1, int x2, int y2) {
    return 1ll * (x1 - x2) * (x1 - x2) + 1ll * (y1 - y2) * (y1 - y2);
}

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i].x, a[i].y);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            l[++cnt].len = dis(a[i].x, a[i].y, a[j].x, a[j].y);
            l[cnt].x1 = a[i].x, l[cnt].x2 = a[j].x;
            l[cnt].y1 = a[i].y, l[cnt].y2 = a[j].y;
            l[cnt].midx = (a[i].x + a[j].x);
            l[cnt].midy = (a[i].y + a[j].y);
        }
    }
    sort(l + 1, l + cnt + 1);
    fail = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (l[fail].midx != l[i].midx || l[fail].midy != l[i].midy) {
            fail = i;
            continue;
        }
        for (int j = fail; j < i; ++j) {
            if (l[i].len != l[j].len) continue;
            ans = max(ans, (ll)(sqrt(dis(l[i].x1, l[i].y1, l[j].x1, l[j].y1)) * sqrt(dis(l[i].x1, l[i].y1, l[j].x2, l[j].y2))));
        }
    }
    cout << ans << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
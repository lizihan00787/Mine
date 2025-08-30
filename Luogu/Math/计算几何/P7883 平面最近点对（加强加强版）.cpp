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

const int N = 4e5 + 5;

int n;
struct pt {
    double x, y;
    pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
};
bool cmpx(pt &a, pt &b) { return a.x == b.x ? (a.y < b.y) : (a.x < b.x); }
bool cmpy(pt &a, pt &b) { return a.y < b.y; }
double dis(pt &a, pt &b) { return 1.0 * sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
vector<pt> p, q;

double calc(int l, int r) {
    if (l == r) return 1e18;
    if (l + 1 == r) return dis(p[l], p[r]);
    int mid = (l + r) >> 1, lin = p[mid].x, cnt = 0;
    double d = min(calc(l, mid), calc(mid + 1, r));
    for (int i = l; i <= r; ++i) if (abs(lin - p[i].x) <= d) q[++cnt] = p[i];
    sort(q.begin() + 1, q.begin() + cnt + 1, cmpy);
    for (int i = 1; i <= cnt; ++i)
        for (int j = i + 1; j <= cnt && (q[j].y - q[i].y) <= d; ++j)
            d = min(d, dis(q[j], q[i]));
    return d;
}

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        p.emplace_back(pt(x, y));
    }
    q.resize(n + 1);
    sort(p.begin(), p.end(), cmpx);
    double ans = calc(0, n - 1);
    printf("%.0lf\n", ans * ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
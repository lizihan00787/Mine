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

namespace CG {
    struct pt {
        ll x, y;
        pt(ll _x = 0, ll _y = 0) { x = _x, y = _y; }
    };
    typedef pt vec;
    const double eps = 1e-8;
    inline int dcmp(double x) { return x < -eps ? -1 : (x > eps ? 1 : 0); }
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator / (const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    inline bool operator == (pt a, pt b) { return (!dcmp(a.x - b.x)) && (!dcmp(a.y - b.y)); }
    inline double Abs(double x) { return x * dcmp(x); }
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline bool cmpx(const pt &a, const pt &b) { return (a.x != b.x) ? a.x < b.x : a.y < b.y; }
    inline double Len(const vec &a) { return sqrt(a.x * a.x + a.y * a.y); }
    inline double dis_PP(pt a, pt b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
    inline ll dis_PP2(pt a, pt b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
    struct line {
        pt s, t;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
    };
    inline void Andrew(vector<pt> &p) {
        vector<pt> q(p.size() << 1);
        sort(p.begin(), p.end(), cmpx);
        int top = -1, n = p.size();
        q[++top] = p[0];
        for (int i = 1; i < n; ++i) {
            while (top && dcmp((q[top - 1] - q[top]) ^ (p[i] - q[top])) >= 0) top--;
            q[++top] = p[i];
        }
        int now = top;
        for (int i = n - 2; i >= 0; --i) {
            while (top > now && dcmp((q[top - 1] - q[top]) ^ (p[i] - q[top])) >= 0) --top;
            q[++top] = p[i];
        }
        if (n > 1) --top;
        p.clear();
        for (int i = 0; i <= top; ++i) p.emplace_back(q[i]);
    }
    inline double S(const pt &x, const pt &y, const pt &z) { return Abs((y - x) ^ (z - x)); }
    inline pair<int, int> diam(vector<pt> &p) {
        int n = p.size();
        double ans = 0;
        int k1 = 0, k2 = 0;
        for (int i = 0, j = 1; i < n; ++i) {
            for (;; j = (j + 1) % n)
                if (dcmp(S(p[j], p[i], p[(i + 1) % n]) - S(p[(j + 1) % n], p[i], p[(i + 1) % n])) >= 0) break;
            double d1 = dis_PP(p[j], p[i]), d2 = dis_PP(p[j], p[(i + 1) % n]);
            if (d1 > ans) ans = d1, k1 = j, k2 = i;
            if (d2 > ans) ans = d2, k1 = j, k2 = (i + 1) % n;
        }
        return make_pair(k1, k2);
    }
}
using namespace CG;

const int N = 1e5 + 20;

int n, k;
vector<pt> p, p1;
priority_queue<ll, vector<ll>, greater<ll> > q;

inline void solve() {
    read(n, k);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        read(x, y);
        p.emplace_back(pt(x, y));
    }
    for (int i = 1; i <= k; ++i) {
        if (p.empty()) break;
        p1 = p; Andrew(p1);
        PII res = diam(p1);
        int x = res.first, y = res.second;
        q.push(dis_PP2(p1[x], p1[y])); if((int)(q.size()) > k) q.pop();
        for (auto it : p) {
            if (it == p1[x] || it == p1[y]) continue;
            q.push(dis_PP2(p1[x], it)); if((int)(q.size()) > k) q.pop();
            q.push(dis_PP2(p1[y], it)); if((int)(q.size()) > k) q.pop();
        }
        vector<pt> s;
        for (auto it : p) {
            if (it == p1[x] || it == p1[y]) continue;
            s.emplace_back(it);
        }
        swap(s, p);
    }
    printf("%lld\n", q.top());
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
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
    const double eps = 1e-8;
    struct pt {
        double x, y;
        pt(double _x = 0, double _y = 0) { x = _x, y = _y; }
        inline double len() { return sqrt(x * x + y * y); }
    } O;
    typedef pt vec;
    inline vec operator + (const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator - (const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator * (const vec &x, double y) { return vec(x.x * y, x.y * y); }
    inline vec operator / (const vec &x, double y) { return vec(x.x / y, x.y / y); }
    inline double operator ^ (const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; }
    inline double operator * (const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; }
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline bool cmpx(const pt &a, const pt &b) { return (a.x != b.x) ? a.x < b.x : a.y < b.y; }
    inline int dcmp(double x) { return (x < -eps) ? -1 : (x > eps ? 1 : 0); }
    inline double Abs(double x) { return x * dcmp(x); }
    
    inline double dis_PP(pt a, pt b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }   
    struct line {
        pt s, t;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
    };
    inline vector<pt> Andrew(vector<pt> &p) {
        vector<pt> q(p.size() << 1);
        sort(p.begin(), p.end(), cmpx);
        int top = 0, n = p.size();
        q[++top] = p[0];
        for (int i = 1; i < n; ++i) {
            while (top >= 2 && dcmp((q[top - 1] - q[top]) ^ (p[i] - q[top])) >= 0) top--;
            q[++top] = p[i];
        }
        int now = top;
        for (int i = n - 2; i >= 0; --i) {
            while (top > now && dcmp((q[top - 1] - q[top]) ^ (p[i] - q[top])) >= 0) --top;
            q[++top] = p[i];
        }
        if (n > 1) --top;
        p.clear();
        for (int i = 1; i <= top; ++i) p.emplace_back(q[i]);
        return p;
    }
    inline bool Left(pt x, pt l, pt r) { return dcmp((l - x) ^ (r - x)) <= 0; }
    inline bool judge_PS(pt a, line b) { return (!dcmp((a - b.s) ^ (b.t - b.s))) && (dcmp((a - b.s) * (a - b.t)) <= 0); }
    inline int include_bs(pt p, vector<pt> &pts) {
        int n = pts.size();
        if (!Left(pts[0], p, pts[1])) return 0;
        if (!Left(pts[0], pts[n - 1], p)) return 0;
        if (judge_PS(p, line(pts[0], pts[1]))) return 2;
        if (judge_PS(p, line(pts[0], pts[n - 1]))) return 2;
        int l = 1, r = n - 2, ans = 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (!Left(pts[0], pts[mid], p))
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        if (!Left(pts[ans], p, pts[(ans + 1) % n])) return 0;
        if (judge_PS(p, line(pts[ans], pts[(ans + 1) % n]))) return 2;
        return 1;
    }
    inline vector<pt> merge(vector<pt> &A, vector<pt> &B) {
        int n = (int)(A.size()), m = (int)(B.size()), tot1 = 0, tot2 = 0;
        vector<pt> p(n + 1), q(m + 1);
        for (int i = 1; i < n; ++i) p[++tot1] = A[i] - A[i - 1]; p[++tot1] = A[0] - A[n - 1];
        for (int i = 1; i < m; ++i) q[++tot2] = B[i] - B[i - 1]; q[++tot2] = B[0] - B[m - 1];
        int i = 1, j = 1, tot = 0;
        pt las = pt(0, 0);
        vector<pt> C(n + m + 1);
        C[0] = las = A[0] + B[0];
        while (i <= n && j <= m) {
            if (dcmp(p[i] ^ q[j]) >= 0) C[++tot] = las + p[i++], las = C[tot];
            else C[++tot] = las + q[j++], las = C[tot];
        }
        while (i <= n) C[++tot] = las + p[i++], las = C[tot];
        while (j <= m) C[++tot] = las + q[j++], las = C[tot];
        C = Andrew(C);
        return C;
    }
}
using namespace CG;

const int N = 1e5 + 20;

int n, m, q;
vector<pt> a, b;


inline void solve() {
    read(n, m, q);
    for (int i = 1; i <= n; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        a.emplace_back(pt(x, y));
    }
    for (int i = 1; i <= m; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        b.emplace_back(pt(-x, -y));
    }
    a = Andrew(a), b = Andrew(b);
    a = merge(a, b);
    for (int i = 1; i <= q; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        if (include_bs(pt(x, y), a)) puts("1");
        else puts("0");
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
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
    inline int dcmp(double x) { return (x < -eps ? -1 : (x > eps ? 1 : 0)); }
    inline double Abs(double x) { return x * dcmp(x); }
    inline double S(pt x, pt y, pt z) { return Abs((z - x) ^ (y - x)); }
    inline double dis_PP(pt a, pt b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
    inline vec rotate_90(const pt &a) { return vec(a.y, -a.x); }
    bool operator < (pt a, pt b) {
		double p = angle(a - O), q = angle(b - O);
		return p != q ? p < q : dis_PP(a, O) < dis_PP(b, O);
    }
    struct line {
        pt s, t;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) { s = _s, t = _t; }
    };
    vector<pt> con(vector<pt> vec) {
        int n = ((int)vec.size());
        for (int i = 1; i < n; ++i) if (vec[i].x < vec[0].x || (vec[i].x == vec[0].x && vec[i].y < vec[0].y)) swap(vec[0], vec[i]);
        O = vec[0];
        sort(vec.begin() + 1, vec.end());
        vector<pt> s(n + 1);
        int ed = 0;
        for (int i = 0; i < n; ++i) {
            while (ed >= 2 && dcmp((s[ed] - s[ed - 1]) ^ (vec[i] - s[ed - 1])) <= 0) --ed;
            s[++ed] = vec[i];
        }
        vector<pt> res;
        for (int i = 1; i <= ed; ++i) res.emplace_back(s[i]);
        return res;
    }
}
using namespace CG;

const int N = 2e5 + 20;

int n;
double ans;
pt ret[5];

inline void solve() {
    read(n);
    vector<pt> a(n);
    for (int i = 0; i < n; ++i) scanf("%lf%lf", &a[i].x, &a[i].y);
    a = con(a);
    n = a.size();
    ans = 1e15;
    for (int i = 0, j = 1, k = 1, z = 1; i < n; ++i) {
        for (; S(a[(j + 1) % n], a[i], a[(i + 1) % n]) > S(a[j], a[i], a[(i + 1) % n]); j = (j + 1) % n); // 最上
        if (i == 1) k = j;
        for (; dcmp((a[(k + 1) % n] - a[k]) * (a[(i + 1) % n] - a[i])) <= 0; k = (k + 1) % n); // 最左
        for (; dcmp((a[(z + 1) % n] - a[z]) * (a[(i + 1) % n] - a[i])) > 0; z = (z + 1) % n); // 最右
        pt A = a[i], B = a[(i + 1) % n], C = a[j], D = a[k], E = a[z];
        double dis = (B - A).len(), H = (S(A, B, C) / (A - B).len());
        double L = Abs(((D - A) * (B - A)) / dis), R = Abs(((E - B) * (B - A)) / dis);
        L = L + R + dis;
        if (L * H < ans) ans = L * H, ret[0] = A, ret[1] = B, ret[2] = C, ret[3] = D, ret[4] = E;
    }
    pt A = ret[0], B = ret[1], C = ret[2], D = ret[3], E = ret[4];
    double dis = (B - A).len(), H = (S(A, B, C) / (A - B).len());
    double L = Abs(((D - A) * (B - A)) / dis), R = Abs(((E - B) * (B - A)) / dis);
    double p = L + R + dis;
    ret[0] = B + ((B - A) * (R / dis));
    ret[1] = ret[0] + rotate_90(B - A) * (-H / dis);
    ret[2] = ret[1] + rotate_90(ret[1] - ret[0]) * (-p / H);
    ret[3] = ret[2] + rotate_90(ret[2] - ret[1]) * (-H / p);
    printf("%.5lf\n", ans);
    int st = 0;
    for (int i = 1; i < 4; ++i) if (ret[i].y < ret[st].y || ((ret[i].y == ret[st].y && ret[i].x < ret[st].x))) st = i;
    for (int i = 0; i < 4; ++i) {
        double x = ret[(st + i) % 4].x, y = ret[(st + i) % 4].y;
        if (Abs(x) < 1e-5) x = 0;
        if (Abs(y) < 1e-5) y = 0;
        printf("%.5lf %.5lf\n", x, y);
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
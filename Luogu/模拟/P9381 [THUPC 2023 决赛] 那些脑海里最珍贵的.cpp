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

const int N = 8;

enum HR { week = 0, average = 1, strong = 2 };
enum Ti { north = 1, south = 0 };
enum AT { B = 1, G = 2, M = 3 };

struct Human {
    HR race;
    string race2;
    int sans, max_sans, Lv;
    double atkbase, defbase;
    int s_sklel;
    int p_sklel;
    AT atktype;
    double armatk;
    bool alive;
    int pos;
    double s_imp;
    int a_ski_lv, a_ski_da;
};

struct Team {
    Human t[8];
    double atk_imp;
    double def_imp;
    double rec_spd;
    int num;
    int tot;
    int lasact;
    string name;
} rk[2];

const double wps[] = {0, 0.013, 0.016, 0.019, 0.022, 0.025}; // w的被动技能
const double wss[] = {0, 0.1, 0.12, 0.15, 0.17, 0.2};        // w的主动技能
const double aps[] = {0, 0.01, 0.02, 0.03, 0.04, 0.05};      // a的被动技能
const double ass[] = {0, 0.06, 0.07, 0.08, 0.09, 0.1};       // a的主动技能
const double sps[] = {0, 0.01, 0.02, 0.03, 0.04, 0.05};      // s的被动技能
const double sss[] = {0, 2.1, 2.17, 2.24, 2.32, 2.4};        // s的主动技能
const int forma[7] = {0, 3, 4, 2, 5, 1, 6};                  // 面对的敌人

double add_pos(int atkerpos, int deferpos) { // 攻击防御方位加成
    double t[] = {1.25, 1, 0.75, 0, 0.75, 1};
    int cz = abs(atkerpos - deferpos) % 6;
    return t[cz];
}
double race_restraint(HR atker, HR defer) { // 种族歧视（雾
    double t[3][3] = { {1, 0.9, 1.1}, {1.1, 1.0, 0.9}, {0.9, 1.1, 1.0} };
    return t[atker][defer];
}
void aft_dead(Team &de, Human &deader) {
    deader.alive = 0;
    de.num--;
    deader.a_ski_lv = 0;
    if (deader.race == 0) de.rec_spd -= wps[deader.p_sklel];
    if (deader.race == 1) de.def_imp -= aps[deader.p_sklel];
    if (deader.race == 2) de.atk_imp -= sps[deader.p_sklel];
    deader.sans = 0;
}

void attack(Human &atker, Human &defer, Team att, Team &def, double A, int attpos, int defpos) {
    if (!defer.alive) return;
    double B = atker.s_imp;
    double C = min(att.atk_imp + 1, 1.1);
    double D = race_restraint(atker.race, defer.race);
    double E = add_pos(attpos, defpos);
    double x = A * B * C * D * E;
    double F = defer.defbase;
    double G = min(def.def_imp + 1, 1.1);
    double y = F * G;
    int z = floor(x / y);
    defer.sans = max(0, defer.sans - z);
    if (defer.sans <= 0) aft_dead(def, defer);
    printf("%d %d took %d damage from %d %d -> %d/%d\n", def.name, defer.pos, z, att.name, atker.pos, defer.sans, defer.max_sans);
}

void com_atk(Human &atker, Human &defer, Team att, Team &def, int attpos, int defpos) {
    attack(atker, defer, att, def, atker.atkbase * atker.armatk, attpos, defpos);
    atker.s_imp = 1;
}
void spe_atk_B(Human &atker, Human &defer, Team att, Team &def, int attpos, int defpos) {
    attack(atker, defer, att, def, atker.atkbase * atker.armatk * 1.25, attpos, defpos);
    atker.s_imp = 1;
}
void spe_atk_G(Human &atker, Human &defer, Team att, Team &def, int defer1, int attpos, int defpos) {
    int s = 1, l = 0, r = 0;
    for (int i = defer1 - 1; i >= 1; --i) 
        if (def.t[i].alive) { s++, l = i; break; }
    for (int i = defer1 + 1; i <= 6; ++i) 
        if (def.t[i].alive) { s++, l = i; break; }
    attack(atker, defer, att, def, atker.atkbase * atker.armatk * 1.35 / s, attpos, defpos);
    if (l) attack(atker, def.t[l], att, def, atker.atkbase * atker.armatk * 1.35 / s, attpos, defpos);
    if (l) attack(atker, def.t[r], att, def, atker.atkbase * atker.armatk * 1.35 / s, attpos, defpos);
    atker.s_imp = 1;
}
void spe_atk_M(Human &atker, Human &defer, Team att, Team &def, int defer1, int attpos, int defpos) {
    int l = 0, r = 0;
    for (int i = defer1 - 1; i >= 1; i--)
        if (def.t[i].alive) { l = i; break; }
    for (int i = defer1 + 1; i <= 6; i++)
        if (def.t[i].alive) { r = i; break; }
    attack(atker, defer, att, def, atker.atkbase * atker.armatk * 1.15, attpos, defpos);
    if (l) attack(atker, def.t[l], att, def, atker.atkbase * atker.armatk * 0.23, attpos, defpos);
    if (r) attack(atker, def.t[r], att, def, atker.atkbase * atker.armatk * 0.23, attpos, defpos);
    atker.s_imp = 1;
}
void w_skill(Human &rec, string atk, double res_imp) {
    if (rec.max_sans == rec.sans || !rec.alive) return;
    int x = floor(rec.max_sans * res_imp);
    if (x <= 0) return;
    rec.sans = min(rec.sans + x, rec.max_sans);
    printf("%s %d recovered +%d hp -> %d/%d\n", atk.c_str(), rec.pos, x, rec.sans, rec.max_sans);
}
void a_skill(Human atker, Human &defer) { defer.a_ski_lv = 3, defer.a_ski_da = floor(defer.max_sans * ass[atker.s_sklel]); }
void s_skill(Human atker, Human &rec) { rec.s_imp = sss[atker.s_sklel]; }

int mover(Team move, int round) {
    int p = 0;
    if (round > 0)
        for (int i = move.lasact + 1; i <= move.tot; ++i)
            if (move.t[forma[i]].alive) return i;
    for (int i = 1; i <= move.tot; ++i)
        if (move.t[forma[i]].alive) return i;
}
void into(Ti a, int n) {
    rk[a].num = n;
    rk[a].tot = n;
    for (int i = 1; i <= n; ++i) {
        int k = forma[i];
        char x[10];
        char c;
        scanf("%s Lv=%d maxhp=%d atk=%lf def=%lf skillLv=%d passivesklLv=%d %c weaponatk=%lf", x, &rk[a].t[k].Lv, &rk[a].t[k].max_sans, &rk[a].t[k].atkbase, &rk[a].t[k].defbase, &rk[a].t[k].a_ski_lv, &rk[a].t[k].p_sklel, &c, &rk[a].t[k].armatk);
        int len = strlen(x);
        for (int j = 0; j < len; ++j) rk[a].t[k].race2 += x[j];
        rk[a].t[k].s_imp = 1;
        rk[a].t[k].sans = rk[a].t[k].max_sans;
        rk[a].t[k].pos = i;
        rk[a].t[k].alive = 1;
        Human t1 = rk[a].t[k];
        if (rk[a].t[k].race2 == "Weak") rk[a].t[k].race = week, rk[a].rec_spd += wps[t1.p_sklel];
        else if (rk[a].t[k].race2 == "Average") rk[a].t[k].race = average, rk[a].def_imp += aps[t1.p_sklel];
        else if (rk[a].t[k].race2 == "Strong") rk[a].t[k].race = strong, rk[a].atk_imp += sps[t1.p_sklel];
        if (c == 'B') rk[a].t[k].atktype = B;
        if (c == 'G') rk[a].t[k].atktype = G;
        if (c == 'M') rk[a].t[k].atktype = M;
    }
}

void summary() {
    printf("North:");
    for (int j = 1; j <= 6; j++)
        if (rk[1].t[j].max_sans)
            printf(" %d/%d", rk[1].t[j].sans, rk[1].t[j].max_sans);
    puts("");
    printf("South:");
    for (int j = 1; j <= 6; j++)
        if (rk[0].t[j].max_sans)
            printf(" %d/%d", rk[0].t[j].sans, rk[0].t[j].max_sans);
    puts("");
    puts("");
}

inline void solve() {
    int n, m, k;
    read(n, m, k);
    rk[1].name = "North";
    rk[0].name = "South";
    into(south, n); into(north, m);
    for (int i = 0; i < k; ++i) {
        Team move = rk[i % 2];
        int l = i % 2, r = (i + 1) % 2, round = (i + 1) / 2;
        for (int j = 1; i <= move.tot; ++j) w_skill(rk[l].t[forma[j]], move.name, min(move.rec_spd, 0.05));
        char x[20];
        scanf("%s ", x);
        int atker1 = mover(move, round);
        int atker2 = forma[atker1];
        rk[l].lasact = atker1;
        if (x[0] == 'B') {
            int defer, attpos, defpos;
            scanf("target=%d atkpos=%d ddgpos=%d", &defer, &attpos, &defpos);
            com_atk(rk[l].t[atker2], rk[r].t[forma[defer]], move, rk[r], attpos, defpos);
        }
        else if (x[1] == 'p') {
            int defer, attpos, defpos;
            scanf("target=%d atkpos=%d ddgpos=%d", &defer, &attpos, &defpos);
            switch (move.t[atker2].atktype) {
            case B:
                spe_atk_B(rk[l].t[atker2], rk[r].t[forma[defer]], move, rk[r], attpos, defpos);
                break;
            case G:
                spe_atk_G(rk[l].t[atker2], rk[r].t[forma[defer]], move, rk[r], forma[defer], attpos, defpos);
                break;
            case M:
                spe_atk_M(rk[l].t[atker2], rk[r].t[forma[defer]], move, rk[r], forma[defer], attpos, defpos);
                break;
            }
        }
        else {
            int rec;
            scanf("target=%d", &rec);
            switch (move.t[atker2].race) {
            case week:
                printf("%s %d applied %s skill to ", move.name, atker1, rk[l].t[atker2].race2);
                printf("%s %d\n", move.name.c_str(), rec);
                cout << move.name << " " << rec << endl;
                w_skill(rk[l].t[forma[rec]], move.name, wss[move.t[atker2].s_sklel]);
                break;
            case average:
                printf("%s %d applied %s skill to ", move.name, atker1, move.t[atker2].race2);
                printf("%s %d\n", rk[r].name.c_str(), rec);
                a_skill(move.t[atker2], rk[r].t[forma[rec]]);
                break;
            case strong:
                printf("%s %d applied %s skill to ", move.name, atker1, rk[l].t[atker2].race2);
                printf("%s %d\n", move.name.c_str(), rec);
                s_skill(move.t[atker2], rk[l].t[forma[rec]]);
                break;
            }
        }
        for (int l = 1; l <= 6; l++) {
            int j = forma[l];
            if (rk[r].t[j].a_ski_lv && rk[r].t[j].alive) {
                rk[r].t[j].sans = max(0, rk[r].t[j].sans - rk[r].t[j].a_ski_da);
                rk[r].t[j].a_ski_lv--;
                printf("%s %d took %d damage from skill -> %d/%d\n", rk[r].name, rk[r].t[j].pos, rk[r].t[j].a_ski_da, rk[r].t[j].sans, rk[r].t[j].max_sans);
                if (rk[r].t[j].sans <= 0) aft_dead(rk[r], rk[r].t[j]);
            }
        }
        summary();
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
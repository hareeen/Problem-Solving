#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

void compress(vector<int> &v) {
    vector<int> zip;
    copy(iterall(v), back_inserter(zip));
    sort(iterall(zip));

    for (auto &el:v) el = lower_bound(iterall(zip), el) - zip.begin();
}

class Node {
public:
    int v;
    Node *l, *r;

    explicit Node(int _v = 0, Node *_l = nullptr, Node *_r = nullptr) {
        v = _v;
        l = _l, r = _r;
    }
};

namespace PST {
    Node *init(int s, int e) {
        auto m = (s + e) / 2;
        if (s == e) return new Node();
        else return new Node(0, init(s, m), init(m + 1, e));
    }

    Node *update(Node *h, int s, int e, int t, int v) {
        auto m = (s + e) / 2;

        if (t < s or e < t) return h;
        if (s == e) return new Node(v);

        auto l = update(h->l, s, m, t, v);
        auto r = update(h->r, m+1, e, t, v);
        return new Node(l->v + r->v, l, r);
    }

    int query(Node *h, int s, int e, int ql, int qr) {
        auto m = (s + e) / 2;

        if (e < ql or qr < s) return 0;
        if (ql <= s and e <= qr) return h->v;
        return query(h->l, s, m, ql, qr) + query(h->r, m+1, e, ql, qr);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<int> v(N);
    for (int i = 0; i < N; i++) cin >> v[i];
    compress(v);

    vector<int> nxel(N);
    unordered_map<int, int> mp;
    for (int i = N - 1; i >= 0; i--) {
        auto it = mp.find(v[i]);
        if (it == mp.end()) nxel[i] = N + 1;
        else nxel[i] = it->second;
        mp[v[i]] = i;
    }

    vector<pi> nxen;
    for (int i = 0; i < N; i++) nxen.emplace_back(nxel[i], i + 1);
    sort(iterall(nxen));

    vector<Node *> pseg;
    pseg.emplace_back(PST::init(1, N));
    for (auto[el, i]:nxen) pseg.emplace_back(PST::update(pseg.back(), 1, N, i, 1));

    int Q;
    cin >> Q;

    int lastq = 0;
    for (int i = 0; i < Q; i++) {
        int s, e;
        cin >> s >> e;

        int pos = lower_bound(iterall(nxen), pi(e, 0)) - nxen.begin();
        lastq = e - s + 1 - PST::query(pseg[pos], 1, N, s, e);
        cout << lastq << '\n';
    }

    return 0;
}
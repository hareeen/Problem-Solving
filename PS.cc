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

const uint baseD = 31;
i64 ans = 0;

class Node {
public:
    uint dep = baseD - 1;
    vector<uint> sorted;
    Node *l = nullptr, *r = nullptr;

    Node() = default;

    explicit Node(uint _dep) {
        dep = _dep;
    }

    void createLeft() {
        if (l) return;
        l = new Node(dep - 1);
    }

    void createRight() {
        if (r) return;
        r = new Node(dep - 1);
    }

    void append(uint x) {
        if (!dep) return;

        if (x & (1u << (dep - 1))) {
            createRight();
            r->append(x);
        } else {
            createLeft();
            l->append(x);
        }
    }

    uint xorFind(uint x) {
        if (!dep) return 0;

        bool bit = (1u << (dep - 1)) & x;
        if (bit) {
            if (r) return r->xorFind(x);
            return l->xorFind(x) + (1u << (dep - 1));
        } else {
            if (l) return l->xorFind(x);
            return r->xorFind(x) + (1u << (dep - 1));
        }
    }

    void collect() {
        if (l) l->collect();
        if (r) r->collect();

        if (dep == 0) {
            sorted.emplace_back(0);
            return;
        }

        if (l && r) {
            uint m = 1u << (dep - 1);
            for (auto el: r->sorted) m = min(m, l->xorFind(el));

            ans += m;
            ans += 1u << (dep - 1);
        }

        if (l) {
            copy(iterall(l->sorted), back_inserter(sorted));
            l->sorted.clear();
        }
        if (r) {
            for (auto &el: r->sorted) el += 1u << (dep - 1);
            copy(iterall(r->sorted), back_inserter(sorted));
            r->sorted.clear();
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Node *root = new Node();

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        uint x;
        cin >> x;
        root->append(x);
    }

    root->collect();
    cout << ans << endl;

    return 0;
}
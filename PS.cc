#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

class Node {
public:
    int s, e, val;
    Node *l, *r;

    Node() {
        s = e = val = 0;
        l = r = nullptr;
    }

    Node(int _s, int _e, int _val) {
        s = _s, e = _e, val = _val;
        l = r = nullptr;
    }

    Node(int _s, int _e, int _val, Node *_l, Node *_r) {
        s = _s, e = _e, val = _val;
        l = _l, r = _r;
    }
};

class psegTree {
public:
    vector<Node *> tree;

    psegTree() {
        tree.clear();
    }

    static Node *init(int s, int e, const vector<int> &arr) {
        if (s == e) return new Node(s, e, arr[s]);
        else {
            auto left = init(s, (s + e) / 2, arr);
            auto right = init((s + e) / 2 + 1, e, arr);
            return new Node(s, e, left->val + right->val, left, right);
        }
    }

    static Node *update(Node *here, const int t, const int d) {
        int s = here->s, e = here->e;
        if (t < s || e < t) return here;
        else if (s <= t && e <= t) return new Node(s, e, here->val + d, here->l, here->r);
        else {
            auto left = update(here->l, t, d);
            auto right = update(here->r, t, d);
            return new Node(s, e, left->val + right->val, left, right);
        }
    }

    void create(Node *toAppend) {
        tree.push_back(toAppend);
    }

    static int query(Node *here, const int l, const int r) {
        int s = here->s, e = here->e;
        if (r < s || e < l) return 0;
        else if (l <= s && e <= r) return here->val;
        else return query(here->l, l, r) + query(here->r, l, r);
    }
};

int solve(int L, int R, const int k, const psegTree &sT, const int N) {
    int l = 1, r = N;
    while (l < r) {
        int mid = (l + r) / 2;
        auto midVal = psegTree::query(sT.tree[R], 1, mid) - psegTree::query(sT.tree[L - 1], 1, mid);
        if (midVal >= k) r = mid;
        else l = mid + 1;
    }

    for (int i = max(1, l - 3); i <= min(N, l + 3); i++) {
        auto val = psegTree::query(sT.tree[R], 1, i) - psegTree::query(sT.tree[L - 1], 1, i);
        if (val >= k) return i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> arr(N);
    for (int i = 0; i < N; i++) cin >> arr[i];

    auto zip = arr;
    sort(iterall(zip));
    zip.erase(unique(iterall(zip)), zip.end());
    for (auto &el:arr) el = (lower_bound(iterall(zip), el) - zip.begin() + 1);

    auto sT = psegTree();
    vector<int> zeros(N + 1);
    sT.create(psegTree::init(1, N, zeros));

    for (auto el:arr) sT.create(psegTree::update(sT.tree.back(), el, 1));
    for (int i = 0; i < Q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << zip[solve(l, r, k, sT, N) - 1] << '\n';
    }

    return 0;
}
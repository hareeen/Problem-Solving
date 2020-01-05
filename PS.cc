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
    int s, e;
    i64 val;
    Node *l, *r;

    Node() {
        s = e = val = 0;
        l = r = nullptr;
    }

    Node(int _s, int _e, i64 _val) {
        s = _s, e = _e, val = _val;
        l = r = nullptr;
    }

    Node(int _s, int _e, i64 _val, Node *_l, Node *_r) {
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

    static Node *init(int s, int e, const vector<i64> &arr) {
        if (s == e) return new Node(s, e, arr[s]);
        else {
            auto left = init(s, (s + e) / 2, arr);
            auto right = init((s + e) / 2 + 1, e, arr);
            return new Node(s, e, left->val + right->val, left, right);
        }
    }

    static Node *update(Node *here, const int t, const i64 d) {
        int s = here->s, e = here->e;
        if (t < s || e < t) return here;
        else if (s == e) return new Node(s, e, here->val + d, here->l, here->r);
        else {
            auto left = update(here->l, t, d);
            auto right = update(here->r, t, d);
            return new Node(s, e, left->val + right->val, left, right);
        }
    }

    void create(Node *toAppend) {
        tree.push_back(toAppend);
    }

    static i64 query(Node *here, const int l, const int r) {
        int s = here->s, e = here->e;
        if (r < s || e < l) return 0;
        else if (l <= s && e <= r) return here->val;
        else return query(here->l, l, r) + query(here->r, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> arr(N + 1);
    for (int i = 1; i <= N; i++) cin >> arr[i];

    auto sT = psegTree();
    sT.create(psegTree::init(1, N, arr));

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int idx, v;
            cin >> idx >> v;
            // cout<<"asdf"<<v - psegTree::query(sT.tree.back(), idx, idx)<<endl;
            sT.create(psegTree::update(sT.tree.back(), idx, v - psegTree::query(sT.tree.back(), idx, idx)));
        } else {
            int k, l, r;
            cin >> k >> l >> r;
            cout << psegTree::query(sT.tree[k], l, r) << '\n';
        }
    }

    return 0;
}
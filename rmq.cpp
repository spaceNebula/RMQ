#include <iostream>
#include <vector>
#include <utility>
#include <functional>

using ll = long long int;

template<typename T>
class RSQ {
private:
    std::vector<T> _data;
    ll _nothing = 0;
    ll _sz;

    [[nodiscard]] ll _left(ll v) const { return 2 * v + 1; }

    [[nodiscard]] ll _right(ll v) const { return 2 * v + 2; }

    [[nodiscard]] ll _parent(ll v) const { return (v - 1) / 2; }

    static T tree_function(const T &lhs, const T &rhs) { return lhs + rhs; }

public:

    explicit RSQ(const std::vector<T> &numbers) {
        ll sz = 1;
        while (sz < numbers.size()) {
            sz *= 2;
        }
        _sz = sz;
        _data.resize(2 * _sz - 1);
        for (auto i = sz - 1; i < 2 * sz - 2; ++i) {
            if (i - _sz + 1 < numbers.size()) {
                _data[i] = numbers[i - sz + 1];
            } else {
                _data[i] = _nothing;
            }
        }
        for (ll i = sz - 2; i >= 0; --i) {
            _data[i] = tree_function(_data[_left(i)], _data[_right(i)]);
        }
    }

    void update(ll current, ll vertex_index, ll x, ll left_border, ll right_border) {
        if (left_border > vertex_index or vertex_index >= right_border) return;
        if (current == vertex_index + _sz - 1) {
            _data[current] = x;
            return;
        }
        auto mid_id = (left_border + right_border) / 2;
        update(_left(current), vertex_index, x, left_border, mid_id);
        update(_right(current), vertex_index, x, mid_id, right_border);
        _data[current] = tree_function(_data[_left(current)], _data[_right(current)]);
    }

    T query_function(ll v, ll ql, ll qr, ll il, ll ir) {
        if (ir <= ql or qr <= il) return 0;

        if (ql <= il and ir <= qr) return _data[v];

        auto im = (il + ir) / 2;
        return tree_function(query_function(_left(v), ql, qr, il, im),
                             query_function(_right(v), ql, qr, im, ir));
    }

    ll extended_size() {
        return _sz;
    }
};

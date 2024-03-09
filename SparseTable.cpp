#include <iostream>
#include <vector>

class SparseTable {

private:
    int N, P;
    std::vector<int> logs;
    std::vector<std::vector<long long>> sparse;
    std::vector<std::vector<int>> index;

    static long long cmp(long long &a, long long &b) {
        return std::min(a, b);
    }

public:
    SparseTable() = default;

    explicit SparseTable(std::vector<long long> &values) {
        init(values);
    }

    void init(std::vector<long long> &values) {
        N = (int) values.size();
        P = (int) std::__lg(N);
        logs.resize(N + 1);
        sparse.resize(P + 1, std::vector<long long>(N));
        index.resize(P + 1, std::vector<int>(N));

        for (int i = 2; i <= N; ++i)
            logs[i] = logs[i / 2] + 1;

        for (int i = 0; i < N; ++i)
            sparse[0][i] = values[i], index[0][i] = i;
        for (int p = 1; p <= P; ++p)
            for (int i = 0; i + (1 << p) <= N; ++i) {
                long long rightValue = sparse[p - 1][i], leftValue = sparse[p - 1][i + (1 << (p - 1))];
                sparse[p][i] = cmp(rightValue, leftValue);
                if (rightValue == cmp(rightValue, leftValue))
                    index[p][i] = index[p - 1][i];
                else index[p][i] = index[p - 1][i + (1 << (p - 1))];
            }
    }


    long long FastQuery(int l, int r) {
///     Time Complexity: O(1)

        --l, --r;
        int p = logs[r - l + 1];
        return cmp(sparse[p][l], sparse[p][r - (1 << p) + 1]);
    }

    long long Query(int l, int r) {
///     Time Complexity: O(log2(N))

        --l, --r;
        long long ans = LLONG_MIN;
        for (int p = logs[r - l + 1]; l <= r; p = logs[r - l + 1]) {
            ans = cmp(ans, sparse[p][l]);
            l += (1 << p);
        }
        return ans;
    }

    long long FastIndexQuery(int l, int r) {
///     Time Complexity: O(1)

        --l, --r;
        int p = logs[r - l + 1];
        long long rightValue = sparse[p][l], leftValue = sparse[p][r - (1 << p) + 1];
        return (rightValue == cmp(rightValue, leftValue) ? index[p][l] : index[p][r - (1 << p) + 1]);
    }

    long long indexQuery(int l, int r) {
///     Time Complexity: O(log2(N))

        --l, --r;
        long long value = LLONG_MIN, ans;
        for (int p = logs[r - l + 1]; l <= r; p = logs[r - l + 1]) {
            if (value != cmp(value, sparse[p][l]))
                ans = index[p][l];
            l += (1 << p);
        }
        return ans;
    }
};
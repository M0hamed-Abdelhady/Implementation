#include <iostream>
#include <vector>

class SparseTable {

private:
    int N, P;
    std::vector<int> logs;
    std::vector<std::vector<long long>> sparse;


public:
    SparseTable() = default;

    SparseTable(std::vector<long long> &values) {
        init(values);
    }

    void init(std::vector<long long> &values) {
        N = (int) values.size();
        P = (int) std::__lg(N);
        logs.resize(N + 1);
        sparse.resize(P + 1, std::vector<long long>(N));

        for (int i = 2; i <= N; ++i)
            logs[i] = logs[i / 2] + 1;

        for (int i = 0; i < N; ++i)
            sparse[0][i] = values[i];
        for (int p = 1; p <= P; ++p)
            for (int i = 0; i + (1 << p) <= N; ++i)
                sparse[p][i] = std::max(sparse[p - 1][i], sparse[p - 1][i + (1 << (p - 1))]);

    }


    long long FastQuery(int l, int r) {
///     Time Complexity: O(1)

        --l, --r;
        int p = logs[r - l + 1];
        return std::max(sparse[p][l], sparse[p][r - (1 << p) + 1]);
    }

    long long Query(int l, int r) {
///     Time Complexity: O(log2(N))

        --l, --r;
        long long ans = LLONG_MIN;
        for (int p = logs[r - l + 1]; l <= r; p = logs[r - l + 1]) {
            ans = std::max(ans, sparse[p][l]);
            l += (1 << p);
        }
        return ans;
    }
};
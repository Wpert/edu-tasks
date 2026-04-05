#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

using ll = long long;

int ans(ll first, ll second, ll third) {
    int tmp = std::max({first, second, third});
    return (tmp < 0LL) ? -1 : tmp;
}

int main() {
    std::ifstream fin("lepus.in");
    std::ofstream fout("lepus.out");

    size_t n{};
    fin >> n;

    std::string field{};
    fin >> field;

    std::vector<int> ladder{};
    ladder.resize(n);
    for (size_t i{}; i < n; ++i) {
        if (field[i] == '.')
            ladder[i] = 0;
        else if (field[i] == '"')
            ladder[i] = 1;
        else
            ladder[i] = std::numeric_limits<int>::min();
    }

    // k -> k + 1
    // k -> k + 3
    // k -> k + 5

    auto dp = std::vector<std::vector<ll>>(
        3,
        std::vector<ll>(
            n,
            std::numeric_limits<int>::min()
        )
    );

    dp[0][0] = ladder[0];
    dp[1][0] = ladder[0];
    dp[2][0] = ladder[0];

    for (size_t i{1}; i < n; ++i) {
        dp[0][i] = std::max({dp[0][i - 1], dp[1][i - 1], dp[2][i - 1]}) + ladder[i];

        if (i >= 3)
            dp[1][i] = std::max({dp[0][i - 3], dp[1][i - 3], dp[2][i - 3]}) + ladder[i];

        if (i >= 5)
            dp[2][i] = std::max({dp[0][i - 5], dp[1][i - 5], dp[2][i - 5]}) + ladder[i];
    }

    fout << ans(dp[0][n - 1], dp[1][n - 1], dp[2][n - 1]) << '\n';
 
    return 0;
}
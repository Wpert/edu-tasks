#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
 
using ll = long long;
 
int main() {
    std::ifstream fin("ladder.in");
    std::ofstream fout("ladder.out");
 
    size_t n{};
    fin >> n;
 
    std::vector<int> ladder{};
    ladder.resize(n);
    for (size_t i{}; i < n; ++i) {
        fin >> ladder[i];
    }
 
    auto dp = std::vector<std::vector<int>>(2, std::vector<int>(n, 0));
 
    dp[0][0] = ladder[0];
    dp[1][0] = std::numeric_limits<int>::min();
 
    dp[0][1] = dp[0][0] + ladder[1];
    dp[1][1] = ladder[1];
 
    for (size_t i{2}; i < n; ++i) {
        dp[0][i] = std::max(dp[0][i - 1], dp[1][i - 1]) + ladder[i];
        dp[1][i] = std::max(dp[0][i - 2], dp[1][i - 2]) + ladder[i];
    }
 
    fout << std::max(dp[0][n - 1], dp[1][n - 1]) << std::endl;
 
    return 0;
}
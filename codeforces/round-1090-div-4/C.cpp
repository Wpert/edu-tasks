#include <iostream>
#include <vector>
#include <algorithm>
 
using ll = long long;
 
int main() {
    int t{};
    std::cin >> t;
    
    for (int i{}; i < t; ++i) {
        int n{};
        std::cin >> n;

        for (int j{}; j < n; ++j) {
            std::cout << j + 1 << ' '
                      << n + 2*j + 1 << ' '
                      << n + 2*j + 2 << ' ';
        }
        std::cout << '\n';
    }
 
    return 0;
}
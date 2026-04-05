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
        std::vector<int> arr{};
        arr.resize(n);
        for (int j{}; j < n; ++j) {
            std::cin >> arr[j];
        }
 
        int maxXOR{};
        for (int j{}; j < n; ++j) {
            for (int k{}; k < n; ++k) {
                if (j == k) {
                    continue;
                }
                maxXOR = std::max(arr[j] ^ arr[k], maxXOR);
            }
        }
        std::cout << maxXOR << '\n';
    }
 
    return 0;
}
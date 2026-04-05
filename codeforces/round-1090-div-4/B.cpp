#include <iostream>
#include <vector>
#include <algorithm>
 
using ll = long long;
 
int main() {
    int t{};
    std::cin >> t;
 
    
    std::vector<int> arr = std::vector(7, 0);
    
    for (int i{}; i < t; ++i) {
        for (int j{}; j < 7; ++j) {
            std::cin >> arr[j];
        }
        std::sort(arr.begin(), arr.end());
 
        ll sum{};
 
        for (int j{}; j < 6; ++j) {
            arr[j] *= -1;
            sum += arr[j];
        }
        sum += arr[6];
 
        std::cout << sum << '\n';
    }
 
    return 0;
}
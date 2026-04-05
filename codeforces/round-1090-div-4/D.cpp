#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

int main() {
    const int N = 1000000;
    std::vector<bool> isPrime(N + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i * i <= N; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::vector<ll> primes{};
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    int t{};
    std::cin >> t;
    
    for (int i{}; i < t; ++i) {
        int n{};
        std::cin >> n;

        for (int j{1}; j <= n; ++j) {
            std::cout << primes[j - 1] * primes[j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
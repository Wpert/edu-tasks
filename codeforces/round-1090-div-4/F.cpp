#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

bool checkIfConstructionPossible(int x, int y) {
    int n = x + y;
    if (n % 2 == 1) {
        return ((n + 1) / 2.0 <= y) &&
               (y <= n) &&
               (0 <= x) &&
               (x <= (n - 1) / 2.0);
    }
    else {
        return (n / 2 <= y) &&
               (y <= n - 1) &&
               (1 <= x) &&
               (x <= n / 2.0);
    }
}

int main() {
    int t{};
    std::cin >> t;
    
    for (int i{}; i < t; ++i) {
        int x{};
        int y{};
        std::cin >> x >> y;

        if (not checkIfConstructionPossible(x, y)) {
            std::cout << "NO\n";
            continue;
        }
        if (x == 1 && y == 0) {
            std::cout << "NO\n";
            continue;
        }

        std::cout << "YES\n";
        if (x == 0 && y == 1) {
            continue;
        }
        int n = x + y;

        int numLeaves{};
        int numCouples{};

        if (n % 2 == 0) {
            numCouples = n - 1 - y;
            numLeaves = n - 1 - 2 * numCouples;
        } else {
            numCouples = n - y;
            numLeaves = n - 1 - 2 * numCouples;
        }

        // we have root = 1
        int nextVertex = 2;

        for (int i = 0; i < numLeaves; ++i) {
            std::cout << 1 << " " << nextVertex << "\n";
            nextVertex++;
        }

        for (int i = 0; i < numCouples; ++i) {
            int rootChild = nextVertex;
            int coupleLeaf = nextVertex + 1;
            std::cout << 1         << " " << rootChild  << "\n";
            std::cout << rootChild << " " << coupleLeaf << "\n";
            nextVertex += 2;
        }

    }

    return 0;
}
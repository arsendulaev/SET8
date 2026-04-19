//
// Created by arsen on 19.04.2026.
//
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::vector<int> prevRow;
    std::vector<int> currRow;
    for (int times = 0; times < n; ++times) {
        std::string s1, s2;
        std::getline(std::cin, s1);
        std::getline(std::cin, s2);
        prevRow.assign(s2.length() + 1, 0);
        currRow.assign(s2.length() + 1, 0);
        for (int i = 0; i <= s2.length(); ++i) {
            prevRow[i] = i;
        }
        for (int i = 1; i <= s1.length(); ++i) {
            currRow[0] = i;
            for (int j = 1; j <= s2.length(); ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    currRow[j] = prevRow[j - 1];
                } else {
                    currRow[j] = 1 + std::min(prevRow[j - 1], std::min(prevRow[j], currRow[j - 1]));
                }
            }
            std::swap(prevRow, currRow);
        }
        std::cout << prevRow[s2.length()] << ' ';
    }
    return 0;
}

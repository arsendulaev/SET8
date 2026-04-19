//
// Created by arsen on 19.04.2026.
//
#include <iostream>
#include <string>
#include <vector>

std::vector<int> countShift(std::string p) {
    std::vector<int> shift(26, p.size());
    for (int i = 0; i < p.size() - 1; ++i) {
        shift[p[i] - 'a'] = p.size() - i - 1;
    }
    return shift;
}

int main() {
    std::string s, p;
    std::vector<int> indices;
    std::cin >> p >> s;
    auto shift = countShift(p);
    int n = p.size() - 1;
    int i = n;
    while (i < s.size()) {
        int j = n;
        int pos = i;
        while (j >= 0 && s[pos] == p[j]) {
            --j;
            --pos;
        }
        if (j == -1) {
            indices.push_back(pos + 1);
        }
        i += shift[s[i] - 'a'];
    }
    std::cout << indices.size() << std::endl;
    for (int index: indices) {
        std::cout << index << "\n";
    }

    return 0;
}

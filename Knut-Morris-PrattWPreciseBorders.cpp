//
// Created by arsen on 19.04.2026.
//
#include <string>
#include <vector>
#include <iostream>

std::vector<int> precisePrefix(std::string s) {
    int pos;
    std::vector pref(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        for (pos = pref[i - 1]; s[i] != s[pos] && pos != 0; pos = pref[pos - 1]) {}
        pref[i] = pos == 0 ? s[0] == s[i] : pos + 1;
    }
    for (int i = 0; i < s.size(); ++i) {
        if (s[i + 1] == s[pref[i]]) {
            pref[i] = pref[i] > 0 ? pref[pref[i] - 1] : 0;
        }
    }
    return pref;
}

int main() {
    std::string s, p;
    std::vector<int> indices;
    std::cin >> p >> s;
    const std::vector<int> pref = precisePrefix(p);
    int i = 0;
    int j = 0;
    while (i < s.size()) {
        while (j > 0 && p[j] != s[i]) {
            j = pref[j - 1];
        }
        if (p[j] == s[i]) {
            j++;
        }
        if (j == p.size()) {
            indices.push_back(i + 1 - static_cast<int>(p.size()));
        }
        i++;
    }
    std::cout << indices.size() << "\n";
    for (const int index : indices) {
        std::cout << index << "\n";
    }
}


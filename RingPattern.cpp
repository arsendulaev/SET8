//
// Created by arsen on 15.04.2026.
//
#include <string>
#include <vector>
#include <iostream>

int main() {
    int pos;
    std::string s;
    std::cin >> s;
    std::vector pref(s.size(), 0);
    for (int i = 1; i < s.size(); i++) {
        for (pos = pref[i - 1]; s[i] != s[pos] && pos != 0; pos = pref[pos - 1]) {}
        pref[i] = pos == 0 ? s[0] == s[i] : pos + 1;
    }
    std::cout << s.length() - pref[s.length() - 1];
}
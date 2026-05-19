//
// Created by arsen on 23.04.2026.
//
#include <iostream>
#include <vector>
#include <string>
#include <queue>

const int MAX_NODES = 1000005;

struct Trie {
    int next[MAX_NODES][26];
    int fail[MAX_NODES];
    int compressed[MAX_NODES];
    int first_pattern[MAX_NODES];
    int nodes_cnt;
    std::vector<int> pattern_len;
    std::vector<int> next_pattern_id;
    std::vector<std::vector<int>> results;
    void init(int n) {
        nodes_cnt = 1;
        for(int i = 0; i < MAX_NODES; ++i) {
            for(int j = 0; j < 26; ++j) next[i][j] = 0;
            fail[i] = 0;
            compressed[i] = 0;
            first_pattern[i] = -1;
        }
        pattern_len.resize(n);
        next_pattern_id.assign(n, -1);
        results.resize(n);
    }
    void addString(const std::string& s, int id) {
        int v = 0;
        pattern_len[id] = s.length();
        for (char c : s) {
            int char_idx = c - 'a';
            if (!next[v][char_idx]) {
                next[v][char_idx] = nodes_cnt++;
            }
            v = next[v][char_idx];
        }
        next_pattern_id[id] = first_pattern[v];
        first_pattern[v] = id;
    }

    void build() {
        std::queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (next[0][i]) {
                q.push(next[0][i]);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                int to = next[v][i];
                int f = fail[v];
                if (to) {
                    fail[to] = next[f][i];
                    if (first_pattern[fail[to]] != -1) {
                        compressed[to] = fail[to];
                    } else {
                        compressed[to] = compressed[fail[to]];
                    }
                    q.push(to);
                } else {
                    next[v][i] = next[f][i];
                }
            }
        }
    }

    void solve(const std::string& text) {
        int v = 0;
        for (int i = 0; i < text.length(); ++i) {
            v = next[v][text[i] - 'a'];
            int temp = v;
            while (temp != 0) {
                if (first_pattern[temp] != -1) {
                    int pid = first_pattern[temp];
                    while (pid != -1) {
                        results[pid].push_back(i - pattern_len[pid] + 2);
                        pid = next_pattern_id[pid];
                    }
                }
                temp = compressed[temp];
            }
        }
    }
};
Trie ac;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string text;
    std::cin >> text;
    int n;
    std::cin >> n;
    ac.init(n);
    for (int i = 0; i < n; ++i) {
        std::string p;
        std::cin >> p;
        ac.addString(p, i);
    }
    ac.build();
    ac.solve(text);
    for (int i = 0; i < n; ++i) {
        std::cout << ac.results[i].size();
        for (int pos : ac.results[i]) {
            std::cout << " " << pos;
        }
        std::cout << "\n";
    }
    return 0;
}
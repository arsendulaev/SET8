//
// Created by arsen on 26.04.2026.
//
#include <iostream>
#include <vector>
#include <string>
#include <queue>

const int MAX_NODES = 1000005;

struct Trie {
    int next_node[MAX_NODES][2];
    int fail[MAX_NODES];
    bool terminal[MAX_NODES];
    int color[MAX_NODES];
    int nodes;
    void init() {
        nodes = 1;
        for (int i = 0; i < MAX_NODES; ++i) {
            next_node[i][0] = next_node[i][1] = 0;
            fail[i] = 0;
            terminal[i] = false;
            color[i] = 0;
        }
    }

    void addString(const std::string & s) {
        int v = 0;
        for (char c : s) {
            int bit = c - '0';
            if (!next_node[v][bit]) {
                next_node[v][bit] = nodes++;
            }
            v = next_node[v][bit];
        }
        terminal[v] = true;
    }

    void build() {
        std::queue<int> q;
        for (int i = 0; i < 2; ++i) {
            if (next_node[0][i]) {
                q.push(next_node[0][i]);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            terminal[v] = terminal[v] | terminal[fail[v]];
            for (int i = 0; i < 2; ++i) {
                if (next_node[v][i]) {
                    fail[next_node[v][i]] = next_node[fail[v]][i];
                    q.push(next_node[v][i]);
                } else {
                    next_node[v][i] = next_node[fail[v]][i];
                }
            }
        }
    }

    bool dfs(int v) {
        color[v] = 1;
        for (int i = 0; i < 2; ++i) {
            int to = next_node[v][i];
            if (terminal[to]) {
                continue;
            }
            if (color[to] == 1) {
                return true;
            }
            if (color[to] == 0) {
                if (dfs(to)) {
                    return true;
                }
            }
        }
        color[v] = 2;
        return false;
    }
};
Trie ac;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    ac.init();
    for (int i = 0; i < n; ++i) {
        std::string  s;
        std::cin >> s;
        ac.addString(s);
    }
    ac.build();
    if (ac.dfs(0)) {
        std::cout << "TAK\n";
    } else {
        std::cout << "NIE\n";
    }
    return 0;
}
//
// Created by arsen on 19.04.2026.
//
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

const int hashBase_ = 131;
const int hashModulo_ = 1e9 + 7;
std::vector<int64_t> hashes;
std::vector<int64_t> reversedHashes;
std::vector<int64_t> basePowers;

int64_t getSubstrHash(const std::vector<int64_t>& hashes, int left, int right) {
    int64_t result = (hashes[right + 1] - hashes[left] * basePowers[right - left + 1]) % hashModulo_;
    if (result < 0) {
        result += hashModulo_;
    }
    return result;
}

bool isSymmetric(int left, int right, int total) {
    if (left < 0 || right >= total) {
        return false;
    }
    int64_t hash = getSubstrHash(hashes, left, right);
    int64_t reversedHash = getSubstrHash(reversedHashes, total - 1 - right, total - 1 - left);
    return hash == reversedHash;
}

int main() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    std::string reversedS = s;
    std::reverse(reversedS.begin(), reversedS.end());
    hashes.assign(n + 1, 0);
    reversedHashes.assign(n + 1, 0);
    basePowers.assign(n + 1, 1);
    for (int i = 0; i < n; ++i) {
        hashes[i + 1] = (hashes[i] * hashBase_ + s[i]) % hashModulo_;
        reversedHashes[i + 1] = (reversedHashes[i] * hashBase_ + reversedS[i]) % hashModulo_;
        basePowers[i + 1] = (basePowers[i] * hashBase_) % hashModulo_;
    }
    int64_t counter = 0;
    for (int center = 0; center < n + 1; ++center) {
        int lowRadius = 0;
        int highRadius = std::min(center, n - 1 - center);
        int maxOddRadius = 0;
        while (lowRadius <= highRadius) {
            int mid = lowRadius + (highRadius - lowRadius) / 2;
            if (isSymmetric(center - mid, center + mid, n)) {
                maxOddRadius = mid + 1;
                lowRadius = mid + 1;
            } else {
                highRadius = mid - 1;
            }
        }
        counter += maxOddRadius;

        lowRadius = 1;
        highRadius = std::min(center + 1, n - 1 - center);
        int maxEvenRadius = 0;
        while (lowRadius <= highRadius) {
            int mid = lowRadius + (highRadius - lowRadius) / 2;
            if (isSymmetric(center - mid + 1, center + mid, n)) {
                maxEvenRadius = mid;
                lowRadius = mid + 1;
            } else {
                highRadius = mid - 1;
            }
        }
        counter += maxEvenRadius;
    }
    std::cout << counter << std::endl;
    return 0;
}
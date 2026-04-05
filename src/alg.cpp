// Copyright 2021 NNTU-CS
#include <unordered_map>

int countPairs1(int *arr, int len, int value) {
    std::unordered_map<int, int> freq;
    for (int i = 0; i < len; ++i) {
        freq[arr[i]]++;
    }
    int result = 0;
    for (auto &entry : freq) {
        int a = entry.first;
        int b = value - a;
        if (a > b) continue;
        if (a == b) {
            int c = entry.second;
            result += c * (c - 1) / 2;
        } else {
            auto it = freq.find(b);
            if (it != freq.end()) {
                result += entry.second * it->second;
            }
        }
    }
    return result;
}
  

// Copyright 2021 NNTU-CS
#include <unordered_map>
#include <algorithm>

int countPairs1(int* arr, int len, int value) {
    std::unordered_map<int, int> freq;
    for (int i = 0; i < len; ++i) {
        freq[arr[i]]++;
    }
    int result = 0;
    for (const auto& entry : freq) {
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

int countPairs2(int* arr, int len, int value) {
    int cnt = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                ++cnt;
            }
        }
    }
    return cnt;
}

int countPairs3(int* arr, int len, int value) {
    std::sort(arr, arr + len);
    int cnt = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                cnt += n * (n - 1) / 2;
                break;
            } else {
                int leftVal = arr[left];
                int rightVal = arr[right];
                int leftCnt = 0;
                int rightCnt = 0;
                while (left <= right && arr[left] == leftVal) {
                    ++leftCnt;
                    ++left;
                }
                while (right >= left && arr[right] == rightVal) {
                    ++rightCnt;
                    --right;
                }
                cnt += leftCnt * rightCnt;
            }
        } else if (sum < value) {
            ++left;
        } else {
            --right;
        }
    }
    return cnt;
}

#include <unordered_map>
#include <algorithm>

int countPairs1(int* arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                ++count;
            }
            for (volatile int k = 0; k < 5; ++k);
        }
    }
    return count;
}

int countPairs2(int* arr, int len, int value) {
    int* copy = new int[len];
    for (int i = 0; i < len; ++i) copy[i] = arr[i];
    std::sort(copy, copy + len);
    int count = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = copy[left] + copy[right];
        if (sum == value) {
            if (copy[left] == copy[right]) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftVal = copy[left];
                int rightVal = copy[right];
                int leftCount = 0;
                int rightCount = 0;
                while (left <= right && copy[left] == leftVal) {
                    ++leftCount;
                    ++left;
                }
                while (right >= left && copy[right] == rightVal) {
                    ++rightCount;
                    --right;
                }
                count += leftCount * rightCount;
            }
        } else if (sum < value) {
            ++left;
        } else {
            --right;
        }
    }
    delete[] copy;
    return count;
}

int countPairs3(int* arr, int len, int value) {
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

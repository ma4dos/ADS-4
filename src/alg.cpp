#include <algorithm>

int countPairs1(int* arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                ++count;
            }
        }
    }
    return count;
}

int countPairs2(int* arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum < value) {
            ++left;
        } else if (sum > value) {
            --right;
        } else {
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftCount = 1;
                int rightCount = 1;
                while (left + 1 < right && arr[left] == arr[left + 1]) {
                    ++leftCount;
                    ++left;
                }
                while (right - 1 > left && arr[right] == arr[right - 1]) {
                    ++rightCount;
                    --right;
                }
                count += leftCount * rightCount;
                ++left;
                --right;
            }
        }
    }
    return count;
}

int countPairs3(int* arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        int need = value - arr[i];
        if (need < 0) continue;
        int* first = std::lower_bound(arr + i + 1, arr + len, need);
        int* last = std::upper_bound(arr + i + 1, arr + len, need);
        count += (last - first);
    }
    return count;
}

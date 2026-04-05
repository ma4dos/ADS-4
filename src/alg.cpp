// Copyright 2021 NNTU-CS
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
    if (len == 0) return 0;
    int* uniq = new int[len];
    int* freq = new int[len];
    int uniqLen = 0;
    uniq[0] = arr[0];
    freq[0] = 1;
    for (int i = 1; i < len; ++i) {
        if (arr[i] == arr[i - 1]) {
            freq[uniqLen]++;
        } else {
            ++uniqLen;
            uniq[uniqLen] = arr[i];
            freq[uniqLen] = 1;
        }
    }
    ++uniqLen;

    int count = 0;
    for (int i = 0; i < uniqLen; ++i) {
        int need = value - uniq[i];
        int left = i, right = uniqLen - 1;
        int j = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (uniq[mid] == need) {
                j = mid;
                break;
            } else if (uniq[mid] < need) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (j != -1) {
            if (i == j) {
                count += freq[i] * (freq[i] - 1) / 2;
            } else {
                count += freq[i] * freq[j];
            }
        }
    }
    delete[] uniq;
    delete[] freq;
    return count;
}

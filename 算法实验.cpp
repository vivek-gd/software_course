#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

// 划分函数，返回基准元素的最终位置
int partition(std::vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (nums[j] <= pivot) {
            ++i;
            std::swap(nums[i], nums[j]);
        }
    }
    std::swap(nums[i + 1], nums[right]);
    return i + 1;
}

// 寻找第k小的数
int findKthSmallest(std::vector<int>& nums, int k) {
    if (k < 1 || k > static_cast<int>(nums.size())) {
        throw std::invalid_argument("k 的值不在有效范围内");
    }
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (true) {
        int pivotIndex = partition(nums, left, right);
        if (pivotIndex == k - 1) {
            return nums[pivotIndex];
        } else if (pivotIndex > k - 1) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
}

int main() {
    int num;
    std::vector<int> S;
    // 读取数组元素
    while (std::cin >> num) {
        S.push_back(num);
        if (std::cin.get() == '\n') {
            break;
        }
    }
    int k;
    // 读取 k 的值
    std::cin >> k;
    try {
        int result = findKthSmallest(S, k);
        std::cout << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}    
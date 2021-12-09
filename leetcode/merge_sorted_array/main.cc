#include <vector>

class Solution {
public:
    static void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n) {
        std::vector<int> result(m + n);
        int nums1Index = 0;
        int nums2Index = 0;
        int resultIndex = 0;
        while (nums1Index < m && nums2Index < n) {
            if (nums1.at(nums1Index) < nums2.at(nums2Index)) {
                result.at(resultIndex) = nums1.at(nums1Index);
                nums1Index++;
            } else {
                result.at(resultIndex) = nums2.at(nums2Index);
                nums2Index++;
            }
            resultIndex++;
        }
        while (nums1Index < m) {
            result.at(resultIndex) = nums1.at(nums1Index);
            nums1Index++;
            resultIndex++;
        }
        while (nums2Index < n) {
            result.at(resultIndex) = nums2.at(nums2Index);
            nums2Index++;
            resultIndex++;
        }
        nums1 = result;
    }
};

int main() {
//    std::vector<int> vec1{1, 2, 3, 0, 0,0};
//    std::vector<int> vec2{2, 5, 6};
    std::vector<int> vec1{2, 0};
    std::vector<int> vec2{1};
    Solution::merge(vec1, 1, vec2, 1);

}
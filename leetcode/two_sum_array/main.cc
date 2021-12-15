#include <vector>
#include <unordered_map>

class Solution {
public:
    static std::vector<int> twoSum(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> complements;
        for (auto i{0}; i < nums.size(); i++) {
//            if (!complements.contains(target - i)) {
            if (complements.find(nums.at(i)) == complements.cend()) {
                complements.emplace(std::make_pair(target - nums.at(i), i));
            } else {
                return std::vector<int>{complements.find(nums.at(i))->second, i};
            }
        }
        return std::vector<int>{};
    }
};

int main() {
    std::vector<int> v1{2, 7, 11, 15};
    Solution::twoSum(v1, 9);
    return 0;
}
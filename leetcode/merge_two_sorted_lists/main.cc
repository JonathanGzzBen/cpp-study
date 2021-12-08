/**
 * Definition for singly-linked list.
 */
#include <memory>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    static ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        if (list1 == nullptr) {
            return list2;
        } else if (list2 == nullptr) {
            return list1;
        }
        auto *mergedListNode = new ListNode();
        auto tail = mergedListNode;
        while (list1 != nullptr || list2 != nullptr) {
            if (list2 == nullptr) {
                tail->next = list1;
                list1 = list1->next;
            } else if (list1 != nullptr && list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        return mergedListNode->next;
    }
};

int main() {
    auto list1 = std::make_unique<ListNode>(1, new ListNode(2, new ListNode(4)));
    auto list2 = std::make_unique<ListNode>(1, new ListNode(3, new ListNode(4)));
    auto result = Solution::mergeTwoLists(list1.get(), list2.get());
    return 0;
}

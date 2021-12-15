struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    static ListNode *reverseList(ListNode *head) {
        ListNode *prev = nullptr;

        while (head != nullptr) {
            auto temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
        }

        return prev;
    }
};

#include <iostream>

void printList(ListNode *head) {
    auto lead = head;
    while (lead != nullptr) {
        std::cout << lead->val << " ";
        lead = lead->next;
    }
    std::cout << std::endl;
}

int main() {
    auto fifthNode = ListNode(5);
    auto fourthNode = ListNode(4, &fifthNode);
    auto thirdNode = ListNode(3, &fourthNode);
    auto secondNode = ListNode(2, &thirdNode);
    auto firstNode = ListNode(1, &secondNode);
    auto result = Solution::reverseList(&firstNode);
    printList(result);
    return 0;
}
#include <iostream>
#include <stack>
#include <vector>
class MyQueue {
private:
    std::stack<int> elements;
public:
    MyQueue() {

    }

    void push(int x) {
        std::stack<int> tempStack;
        while(!elements.empty()) {
            tempStack.push(elements.top());
            elements.pop();
        }
        tempStack.push(x);
        while(!tempStack.empty()) {
            elements.push(tempStack.top());
            tempStack.pop();
        }
    }

    int pop() {
        auto aux{elements.top()};
        elements.pop();
        return aux;
    }

    int peek() {
        return elements.top();
    }

    bool empty() {
        return elements.empty();
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto queue = MyQueue{};
    for(int i{0}; i < 5; i++) {
        queue.push(i);
    }
    std::vector<int> expected{0, 1, 2, 3, 4};
    std::vector<int> result;
    while(!queue.empty()) {
        result.push_back(queue.pop());
    }
    if (expected == result) {
        std::cout << "Correct result" << std::endl;
    } else {
        std::cout << "Result does not match expected result" << std::endl;
    }

    return 0;
}

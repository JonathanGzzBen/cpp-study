#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

namespace {

int Precedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    default:
      return 0;
  }
}

int SolveOperation(int operand1, int operand2, char op) {
  switch (op) {
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '/':
      if (operand2 == 0) throw std::invalid_argument{"Division by zero"};
      return operand1 / operand2;
    default:
      throw std::invalid_argument{"Operator not supported"};
  }
}

void EvaluateNextSubExpression(std::stack<int> *operands,
                               std::stack<char> *operators) {
  auto operand2{operands->top()};
  operands->pop();
  auto operand1{operands->top()};
  operands->pop();

  char op = operators->top();
  operators->pop();

  operands->emplace(SolveOperation(operand1, operand2, op));
}

int EvaluateExpression(const std::string_view &expression) {
  std::stack<int> operands;
  std::stack<char> operators;
  for (auto it{expression.cbegin()}; it != expression.cend(); it++) {
    if (*it == ' ') {
      continue;
    } else if (*it == '(') {
      operators.emplace(*it);
    } else if (std::isdigit(*it)) {
      int operand = 0;
      while (it != expression.cend() && std::isdigit(*it)) {
        operand = (operand * 10) + (*it - '0');
        ++it;
      }
      operands.emplace(operand);
      --it;
    } else if (*it == ')') {
      while (!operators.empty() && operators.top() != '(') {
        EvaluateNextSubExpression(&operands, &operators);
      }

      if (!operators.empty()) operators.pop();

    } else {
      while (!operators.empty() &&
             Precedence(operators.top()) >= Precedence(*it)) {
        EvaluateNextSubExpression(&operands, &operators);
      }

      operators.push(*it);
    }
  }

  while (!operators.empty()) EvaluateNextSubExpression(&operands, &operators);

  return operands.top();
}

}  // namespace

int main(int argc, char **argv) {
  using std::cout;
  using std::endl;
  if (argc == 1) {
    cout << "Usage: arithmetic_expression <expression>\n"
         << "Expression must be enclosed in double quotes" << endl;
    return 1;
  }

  std::string expression{argv[1]};
  try {
    cout << EvaluateExpression(expression) << endl;
  } catch (const std::exception &e) {
    cout << "Error: " << e.what() << endl;
  }
  return 0;
}

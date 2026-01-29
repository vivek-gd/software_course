#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

// 判断字符是否为操作符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

// 获取操作符优先级
int getPriority(char op) {
    switch (op) {
    case '^': return 3;
    case '*': case '/': case '%': return 2;
    case '+': case '-': return 1;
    default: return 0;
    }
}

// 中缀表达式转后缀表达式
string infixToPostfix(const string& infix) {
    stack<char> operatorStack;
    string postfix = "";

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];

        if (isdigit(c) || c == '.') {
            // 处理操作数
            while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix += infix[i];
                ++i;
            }
            postfix += ' ';
            --i;
        }
        else if (c == '(') {
            operatorStack.push(c);
        }
        else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            if (operatorStack.empty()) {
                return ""; // 括号不匹配
            }
            operatorStack.pop(); // 弹出 '('
        }
        else if (isOperator(c)) {
            while (!operatorStack.empty() && getPriority(operatorStack.top()) >= getPriority(c)) {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
        else if (isspace(c)) {
            continue;
        }
        else {
            return ""; // 非法字符
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top() == '(') {
            return ""; // 括号不匹配
        }
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
    }

    return postfix;
}

// 计算后缀表达式的值
double evaluatePostfix(const string& postfix) {
    stack<double> operandStack;
    istringstream iss(postfix);
    string token;

    while (iss >> token) {
        if (isdigit(token[0]) || token[0] == '.') {
            double num;
            istringstream(token) >> num;
            operandStack.push(num);
        }
        else if (isOperator(token[0])) {
            if (operandStack.size() < 2) {
                return NAN; // 操作数不足
            }
            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();

            switch (token[0]) {
            case '+': operandStack.push(operand1 + operand2); break;
            case '-': operandStack.push(operand1 - operand2); break;
            case '*': operandStack.push(operand1 * operand2); break;
            case '/': if (operand2 == 0) return NAN; operandStack.push(operand1 / operand2); break;
            case '%': if (operand2 == 0) return NAN; operandStack.push(fmod(static_cast<int>(operand1), static_cast<int>(operand2))); break;
            case '^': operandStack.push(pow(operand1, operand2)); break;
            }
        }
    }

    if (operandStack.size() != 1) {
        return NAN; // 操作数和操作符不匹配
    }

    return operandStack.top();
}

int main() {
    string infix;
    while (getline(cin, infix)) {
        string postfix = infixToPostfix(infix);
        if (postfix.empty()) {
            cout << "ERROR IN INFIX NOTATION" << endl;
        }
        else {
            double result = evaluatePostfix(postfix);
            if (isnan(result)) {
                cout << "ERROR IN INFIX NOTATION" << endl;
            }
            else {
                cout << fixed << setprecision(2) << result << endl;
            }
        }
    }

    return 0;
}

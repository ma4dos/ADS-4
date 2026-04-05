#include <string>
#include <stack>
#include <cctype>
#include <vector>
#include <sstream>
#include <stdexcept>

static int getPriority(char op) {
    switch (op) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 0;
    }
}

static bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infx2pstfx(const std::string& inf) {
    std::stack<char> opStack;
    std::vector<std::string> tokens;

    for (char ch : inf) {
        if (std::isalnum(ch)) {
            tokens.push_back(std::string(1, ch));
        }
        else if (isOperator(ch)) {
            while (!opStack.empty() && opStack.top() != '(' &&
                   getPriority(opStack.top()) >= getPriority(ch)) {
                tokens.push_back(std::string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(ch);
        }
        else if (ch == '(') {
            opStack.push(ch);
        }
        else if (ch == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                tokens.push_back(std::string(1, opStack.top()));
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            } else {
                throw std::runtime_error("Mismatched parentheses");
            }
        }
    }

    while (!opStack.empty()) {
        tokens.push_back(std::string(1, opStack.top()));
        opStack.pop();
    }

    std::string result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i > 0) result += ' ';
        result += tokens[i];
    }
    return result;
}

int eval(const std::string& post) {
    std::stack<int> st;
    std::stringstream ss(post);
    std::string item;

    while (ss >> item) {
        if (item.size() == 1 && isOperator(item[0])) {
            if (st.size() < 2) throw std::runtime_error("Not enough operands");
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            char op = item[0];
            int res;
            if (op == '+') res = a + b;
            else if (op == '-') res = a - b;
            else if (op == '*') res = a * b;
            else if (op == '/') {
                if (b == 0) throw std::runtime_error("Division by zero");
                res = a / b;
            }
            else throw std::runtime_error("Unknown operator");
            st.push(res);
        }
        else {
            st.push(std::stoi(item));
        }
    }
    if (st.size() != 1) throw std::runtime_error("Invalid expression");
    return st.top();
}

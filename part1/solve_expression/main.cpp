#include <iostream>
#include "Stack.h"
#include "String.h"
#include "Vector.h"

struct element {
    int value;
    bool is_sign;
};

void operation_dispatcher(char sign, vic::Stack<char>& operations, vic::Vector<element>& postfix) {
    if (operations.empty()) {
        operations.push(sign);
        return;
    }

    switch (sign) {
        case '(' : {
            operations.push(sign);
            break;
        }

        case ')' : {
            while (operations.top() != '(') {
                postfix.push({operations.pop(), true});
            }
            operations.pop();
            break;
        }

        case '/':
            //no break
        case '*' : {
            char temp = operations.top();
            while (temp == '/' || temp == '*') {
                temp = operations.pop();
                postfix.push({temp, true});

                if (operations.empty()) {
                    break;
                }
                temp = operations.top();
            }
            operations.push(sign);
            break;
        }

        case '-':
            //no break
        case '+' : {
            char temp = operations.top();
            while (temp != '(' && temp != ')') {
                temp = operations.pop();
                postfix.push({temp, true});

                if (operations.empty()) {
                    break;
                }
                temp = operations.top();
            }
            operations.push(sign);
            break;
        }

        default: {
        }
    }

}

int get_number(vic::String& infix, std::size_t& i) {
    int value = 0;

    while (i < infix.length() && isdigit(infix[i])) {
        value = value * 10 + infix[i] - '0';
        ++i;
    }
    --i;

    return value;
}

void fill_postfix(vic::String& infix, vic::Vector<element>& postfix) {
    vic::Stack<char> operations;

    for (std::size_t i = 0; i < infix.length(); i++) {

        if (isdigit(infix[i])) {
            postfix.push({get_number(infix, i), false});
            continue;
        }

        operation_dispatcher(infix[i], operations, postfix);

    }

    while (!operations.empty()) {
        postfix.push({operations.pop(), true});
    }
}

int solve(vic::Vector<element>& postfix) {
    int result = 0;
    vic::Stack<int> numbers;

    for (std::size_t i = 0; i < postfix.size(); i++) {
        while (!postfix[i].is_sign) {
            numbers.push(postfix[i].value);
            ++i;
        }

        char sign = static_cast<char>(postfix[i].value);
        switch (sign) {
            case '+' : {
                result = numbers.pop() + numbers.pop();
                break;
            }

            case '-' : {
                int first = numbers.pop();
                int second = numbers.pop();
                result = second - first;
                break;
            }

            case '*' : {
                result = numbers.pop() * numbers.pop();
                break;
            }

            case '/' : {
                int first = numbers.pop();
                int second = numbers.pop();
                result = second / first;
                break;
            }

            default: {
            }
        }
        numbers.push(result);
    }

    return numbers.top();
}

int main() {
    vic::String infix_str;
    std::cin >> infix_str;

    vic::Vector<element> postfix;
    fill_postfix(infix_str, postfix);

    std::cout << solve(postfix);

    return 0;
}

#include<iostream>
#include <string>
#include<vector>
using namespace std;

//ASSIGNMENT 2 : DATA 1 
// NAME: AIMEN AHMED AL MILADI 
// UID: 218 010 79 52
template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    // Adds an element to the top of the stack
    void push(T const& element) {
        elements.push_back(element);
    }

    // Removes the top element from the stack
    void pop() {
        if (elements.empty()) {
            throw std::out_of_range("Stack::pop(): empty stack");
        }
        elements.pop_back();
    }

    // Returns the top element of the stack
    T top() const {
        if (elements.empty()) {
            throw std::out_of_range("Stack::top(): empty stack");
        }
        return elements.back();
    }

    // Returns true if the stack is empty, false otherwise
    bool empty() const {
        return elements.empty();
    }

    // Returns the number of elements in the stack
    size_t size() const {
        return elements.size();
    }
};

bool checkParentheses(string equation) {
    Stack<char> s;
    for (char c : equation) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty() || s.top() != '(') {
                cout<< "More right brackets than left";
                return false;
            }
            s.pop();
        }
    }
    if (!s.empty()) {
        cout<< "More left brackets than right";
        return false;
    }
    cout<< "Balanced";
    return true;
}
// This function evaluates a mathematical expression represented as a string
int evaluateExpression(string expression) {
    // Create two stacks, one for operands and one for operators
    Stack<int> operandStack;
    Stack<char> operatorStack;

    // Iterate over each character in the expression
    for (int index = 0; index < expression.length(); index++) {
        // Ignore spaces
        if (expression[index] == ' ') continue;
        // If the character is an opening parenthesis, push it onto the operator stack
        else if (expression[index] == '(') operatorStack.push(expression[index]);
        // If the character is a digit, extract the full number and push it onto the operand stack
        else if (isdigit(expression[index])) {
            int number = 0;
            while (index < expression.length() && isdigit(expression[index])) {
                number = (number * 10) + (expression[index] - '0');
                index++;
            }
            operandStack.push(number);
            index--;
        }
        // If the character is a closing parenthesis, pop operators from the operator stack and apply them to operands from the operand stack until an opening parenthesis is encountered
        else if (expression[index] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                int operand2 = operandStack.top();
                operandStack.pop();
                int operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                switch (op) {
                    case '+': operandStack.push(operand1 + operand2); break;
                    case '-': operandStack.push(operand1 - operand2); break;
                    case '*': operandStack.push(operand1 * operand2); break;
                    case '/': operandStack.push(operand1 / operand2); break;
                }
            }
            operatorStack.pop();
        }
        // If the character is an operator, pop operators from the operator stack and apply them to operands from the operand stack until an opening parenthesis or lower precedence operator is encountered, then push the current operator onto the operator stack
        else {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                int operand2 = operandStack.top();
                operandStack.pop();
                int operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                switch (op) {
                    case '+': operandStack.push(operand1 + operand2); break;
                    case '-': operandStack.push(operand1 - operand2); break;
                    case '*': operandStack.push(operand1 * operand2); break;
                    case '/': operandStack.push(operand1 / operand2); break;
                }
            }
            operatorStack.push(expression[index]);
        }
    }

    // After processing all characters in the expression, pop any remaining operators from the operator stack and apply them to operands from the operand stack
    while (!operatorStack.empty()) {
        int operand2 = operandStack.top();
        operandStack.pop();
        int operand1 = operandStack.top();
        operandStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        switch (op) {
            case '+': operandStack.push(operand1 + operand2); break;
            case '-': operandStack.push(operand1 - operand2); break;
            case '*': operandStack.push(operand1 * operand2); break;
            case '/': operandStack.push(operand1 / operand2); break;
        }
    }

    // The final result is at the top of the operand stack
    return operandStack.top();
}
// This function evaluates a mathematical expression from left to right
int evaluateLeftToRight(string equation) {
    // Create two stacks, one for numbers and one for operators
    Stack<int> numberStack;
    Stack<char> operatorStack;
    string numberString = "";
    // Iterate over each character in the equation
    for (int index = 0; index < equation.length(); index++) {
        // If the character is a digit, add it to the numberString
        if (isdigit(equation[index])) {
            numberString += equation[index];
        } else if (equation[index] != ' ') {
            // If the character is an operator, convert the numberString to an integer and push it onto the numberStack
            numberStack.push(stoi(numberString));
            numberString = "";
            // Apply all operators in the operatorStack to numbers from the numberStack
            while (!operatorStack.empty()) {
                int num1 = numberStack.top();
                numberStack.pop();
                int num2 = numberStack.top();
                numberStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                int result;
                switch (op) {
                    case '+':
                        result = num2 + num1;
                        break;
                    case '-':
                        result = num2 - num1;
                        break;
                    case '*':
                        result = num2 * num1;
                        break;
                    case '/':
                        result = num2 / num1;
                        break;
                }
                numberStack.push(result);
            }
            // Push the current operator onto the operatorStack
            operatorStack.push(equation[index]);
        }
    }
    // Convert the last numberString to an integer and push it onto the numberStack
    numberStack.push(stoi(numberString));
    // Apply any remaining operators in the operatorStack to numbers from the numberStack
    while (!operatorStack.empty()) {
        int num1 = numberStack.top();
        numberStack.pop();
        int num2 = numberStack.top();
        numberStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        int result;
        switch (op) {
            case '+':
                result = num2 + num1;
                break;
            case '-':
                result = num2 - num1;
                break;
            case '*':
                result = num2 * num1;
                break;
            case '/':
                result = num2 / num1;
                break;
        }
        numberStack.push(result);
    }
    // The final result is at the top of the numberStack
    return numberStack.top();
}
// This function evaluates a mathematical expression from right to left
int solveRightToLeft(string equation) {
    // Create two stacks, one for numbers and one for operators
    Stack<int> numberStack;
    Stack<char> operatorStack;
    string numberString = "";
    // Iterate over each character in the equation
    for (int index = 0; index < equation.length(); index++) {
        // If the character is a digit, add it to the numberString
        if (isdigit(equation[index])) {
            numberString += equation[index];
        } else if (equation[index] != ' ') {
            // If the character is an operator, convert the numberString to an integer and push it onto the numberStack
            numberStack.push(stoi(numberString));
            numberString = "";
            // Push the current operator onto the operatorStack
            operatorStack.push(equation[index]);
        }
    }
    // Convert the last numberString to an integer and push it onto the numberStack
    numberStack.push(stoi(numberString));
    // Apply all operators in the operatorStack to numbers from the numberStack
    while (!operatorStack.empty()) {
        int num1 = numberStack.top();
        numberStack.pop();
        int num2 = numberStack.top();
        numberStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        int result;
        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
        }
        numberStack.push(result);
    }
    // The final result is at the top of the numberStack
    return numberStack.top();
}
int choice() {
    // Display the menu options
    cout << endl << "1. Precedence from left to right." << endl;
    cout << "2. No Precedence and one associativity rule (right to left)." << endl;
    cout << "3. No Precedence and one associativity rule (left to right)." << endl;
    cout << "4. Exit" << endl;

    // Get the user's choice
    int userChoice;
    cin >> userChoice;

    // Validate the user's choice
    while (userChoice < 1 || userChoice > 4) {
        cout << "\033[31mInvalid input Mr User , try again: \033[0m";
        cin >> userChoice;
    }

    return userChoice;
}
void inputEquation(string &eq)
{
    cin.ignore();
    cout<<"\033[34m Please Enter your equation : \033[0m";
    getline(cin, eq);
    if(!checkParentheses(eq)){
        exit(1);
    }
}
int main() {
    // Display student information
    cout << "\033[34m Computer Science Department\033[0m" << endl << " \033[34mCS331 Data Structures & Algorithms I\033[0m" << endl << "\033[34m Assignment #2\033[0m"
         << endl << "\033[31mStudent No: 218 010 79 52\033[0m" << endl << "\033[31mStudent Name: Aimen Ahmed Al miladi\033[0m" << endl;

    string equation;
    while (true) {
        // Display the menu and get the user's choice
        switch (choice()) {
            // Evaluate the equation using precedence from left to right
            case 1:
                inputEquation(equation);
                cout << "Your Equation is : " << "\033[31m"<< equation<<"\033[0m" << endl;
                cout << "Result is : " << "\033[32m"<<evaluateExpression(equation)<<"\033[0m";
                break;
            // Evaluate the equation using no precedence and right-to-left associativity
            case 2:
                inputEquation(equation);
                cout << "Your Equation is : " << "\033[31m"<< equation<<"\033[0m" << endl;
                cout << "Result is : " << "\033[32m"<<solveRightToLeft(equation)<<"\033[0m";
                break;
            // Evaluate the equation using no precedence and left-to-right associativity
            case 3:
                inputEquation(equation);
                cout << "Your Equation is : " << "\033[31m"<< equation<<"\033[0m" << endl;
                cout << "Result is : " << "\033[32m"<<evaluateLeftToRight(equation)<<"\033[0m";
                break;
            // Exit the program
            case 4:
                exit(1);
                break;
            // Handle invalid input
            default:
                cout << "\033[31mInvalid input, try again: \033[0m";
                break;
        }
    }
}
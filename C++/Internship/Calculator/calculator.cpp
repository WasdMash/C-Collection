#include <iostream>  // Added for cout, cin, endl
#include <string>
#include <stack>
#include <stdexcept>  // Added for runtime_error and exception classes
#include <vector>
#include <cctype> //Used for anything ASCII-related, such as checking if a character is a number
#include <cmath> //Used this because I'm too lazy to manually code exponentiation as repeated multiplication

using namespace std;

//Division by zero exception class - fixed syntax
class ZeroDivisionError : public exception {
public:
    const char* what() const noexcept override {
        return "You cannot divide by 0 - answer undetermined";
    }
};

// Function to check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to check if a string is a number
bool isNumber(const string& str) {
    if (str.empty()) return false;
    
    bool hasDecimal = false;
    int start = 0;
    
    // Handle negative numbers
    if (str[0] == '-') {
        if (str.length() == 1) return false;
        start = 1;
    }
    
    for (int i = start; i < str.length(); i++) {
        if (str[i] == '.') {
            if (hasDecimal) return false; // Multiple decimals
            hasDecimal = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

//Uses BIDMAS to determine which operators are calculated first
int prec(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

vector<string> tokenize(string s) {
    vector<string> tokens;
    string currentToken = "";
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        
        // Skip whitespace
        if (c == ' ') continue;
        
        // If it's a digit or decimal point, build the number
        if (isdigit(c) || c == '.') {
            currentToken += c;
        }
        // If we hit an operator or parenthesis, save the current number (if any)
        else if (isOperator(c) || c == '(' || c == ')') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken = "";
            }
            tokens.push_back(string(1, c)); // Add operator/parenthesis as single char string
        }
    }
    
    // Don't forget the last token if it exists
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }
    
    return tokens;
}

vector<string> infixToPostfix(string s) {
    stack<string> st;
    vector<string> result;
    
    // First, tokenize the input
    vector<string> tokens = tokenize(s);
    
    for (string token : tokens) {
        // If token is a number, add it to result - fixed logic
        if (isNumber(token)) {
            result.push_back(token);
        }
        // If token is '(', push to stack
        else if (token == "(") {
            st.push(token);
        }
        // If token is ')', pop until we find '('
        else if (token == ")") {
            while (!st.empty() && st.top() != "(") {
                result.push_back(st.top());
                st.pop();
            }
            if (!st.empty()) st.pop(); // Remove the '('
        }
        // If token is an operator
        else if (isOperator(token[0])) {
            while (!st.empty() && st.top() != "(" && 
                   prec(token[0]) <= prec(st.top()[0])) {
                result.push_back(st.top());
                st.pop();
            }
            st.push(token);
        }
    }
    
    // Pop remaining operators from stack
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    
    return result;
}

double performOperation(double operand1, double operand2, char op) {
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': 
            if (operand2 == 0) {
                throw ZeroDivisionError(); // Fixed: create instance of exception
            }
            return operand1 / operand2;
        case '^': return pow(operand1, operand2);
        default:
            throw runtime_error("Unknown operator: " + string(1, op));
    }
}

int main(){
    try {
        //Take in the user's input of an equation
        string equation;
        cout << "Please enter your equation: " << endl;
        getline(cin, equation); // Changed to getline to handle spaces in input

        //Create the postfix stack of the equation to then use for the calculations
        vector<string> calculator = infixToPostfix(equation);

        if (calculator.empty()) { // Fixed variable name
            throw runtime_error("Empty postfix expression");
        }
        
        stack<double> operandStack;
        
        for (const string& token : calculator) {
            if (isNumber(token)) {
                // Convert string to double and push to stack
                double num = stod(token);
                operandStack.push(num);
            }
            else if (token.length() == 1 && isOperator(token[0])) {
                // Make sure we have at least 2 operands
                if (operandStack.size() < 2) {
                    throw runtime_error("Invalid postfix expression: insufficient operands for operator " + token);
                }
                
                // Pop two operands (note the order!)
                double operand2 = operandStack.top(); operandStack.pop();
                double operand1 = operandStack.top(); operandStack.pop();
                
                // Perform operation and push result back
                double result = performOperation(operand1, operand2, token[0]);
                operandStack.push(result);
            }
            else {
                throw runtime_error("Invalid token in postfix expression: " + token);
            }
        }
        
        // Should have exactly one value left in stack
        if (operandStack.size() != 1) {
            throw runtime_error("Invalid postfix expression: incorrect number of operands");
        }
        
        cout << "The answer: " << operandStack.top() << endl; // Fixed output operators
        
    }
    catch (const ZeroDivisionError& e) {
        cout << "Maths error: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "This is what crashed the code: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
    }
    
    return 0;
}
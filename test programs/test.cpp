#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char operation;

    // User input for numbers and operation
    // flush ensures that cout output is written 
    // immediately to the console.
    cout << "Enter first number: " << flush;
    cin >> num1;
    cout << "Enter operator (+, -, *, /): " << flush;
    cin >> operation;
    cout << "Enter second number: " << flush;
    cin >> num2;

    // Switch case for different operations
    switch (operation) {
        case '+':
            cout << "Result: " << num1 + num2 << endl;
            break;
        case '-':
            cout << "Result: " << num1 - num2 << endl;
            break;
        case '*':
            cout << "Result: " << num1 * num2 << endl;
            break;
        case '/':
            // Check for division by zero
            if (num2 != 0) {
                cout << "Result: " << num1 / num2 << endl;
            } else {
                cout << "Error: Division by zero!" << endl;
            }
            break;
        default:
            cout << "Invalid operator!" << endl;
            break;
    }

    return 0;
}
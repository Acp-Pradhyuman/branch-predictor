#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to check if the string is a palindrome
bool isPalindrome(const string& str) {
    int left = 0;
    int right = str.length() - 1;

    // Compare characters from both ends of the string
    while (left < right) {
        if (str[left] != str[right]) {
            return false; // Not a palindrome
        }
        left++;
        right--;
    }
    return true; // It is a palindrome
}

int main() {
    string input;
    
    cout << "Enter a string: " << flush; // Ensures the prompt is immediately shown
    getline(cin, input);

    // Convert to lowercase for case-insensitive comparison
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if (isPalindrome(input)) {
        cout << "The string is a palindrome." << flush << endl;
    } else {
        cout << "The string is not a palindrome." << flush << endl;
    }

    return 0;
}
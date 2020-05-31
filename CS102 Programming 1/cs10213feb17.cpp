/*
    Feb 13, 2017
    Write a program that requests 2 char from the user. Have the program
    display a worning message if the chars are both equal to 'a'. If not, 
    display a welcome message if the chars are both 'z'. If not, check that
    the 1st char is 'c' and the second char is 'd'. In that case print both chars.
    If all the previous conditions are false, print the 1st char.
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    
    char char1, char2;
    
    cout << "Enter the first character" << endl;
    cin >> char1;
    cout << "Enter the second character" << endl;
    cin >> char2;
    
    if (char1 == 'a' && char2 == 'a')
        cout << "Warning" << endl;
    else if (char1 == '3' && char2 == '3')
        cout << "Welcome" << endl;
    else if (char1 == 'c' && char2 == 'd')
        cout << char1 << " " << char2 << endl;
    else 
        cout << char1 << endl;
    
    return 0;
}


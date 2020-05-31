/*
Write a program that requests an integer from the user. The program should
then request a firstname if the integer is less than 20.
*/


#include <iostream>
#include <string>

using namespace std;

int main() {
    
    int user_int;
    string first_name;
    
    cout << "Please enter an integer" << endl;
    cin >> user_int;
    cin.ignore();
    
    if (user_int < 20) {
        cout << "Please enter your firstname" << endl;
        getline(cin, first_name);
        
        cout << "Hello there " << first_name << "." << endl;
    }    
    
    return 0;
}

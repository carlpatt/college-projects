/*
    Feb 13, 2017
    Given the word cat. We would likd the user to spell the word,
    one char at a time. Once the user gets the first chatacter, move 
    onto the next char and test it. The program ens at the 1st mistake.
*/

#include <iostream>

using namespace std;

int main() {
    
    char char1, char2, char3;
    
    cout << "Enter the first letter" << endl;
    cin >> char1;
        
    if (char1 == 'c') {
        cout << "Enter the second letter" << endl;
        cin >> char2;
    }
        
        if (char2 == 'a') {
            cout << "Enter the tird letter" << endl;
            cin >> char3;
        }
            if (char3 == 't')
                cout << "You win!" << endl;
    
    else
        cout << "Incorrect letter!" << endl;
    return 0;
}


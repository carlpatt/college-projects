#include <stdlib.h>
#include <iostream>
/* 
 * ===  FUNCTION  ======================================================================
 *   Name:  main
 *  Description: Write a program using the while loop that keep on requesting an int 
 *  from the user until the user enters 26.  
 * =====================================================================================
 */


using namespace std;

int main () {
    
    int user_input;
    
    cout << "Please enter and integer" << endl;
    cin >> user_input; 

    while (user_input != 26) {
        cout << "Wrong number please try again." << endl;
        cin >> user_input;
    }
    
    cout << "You got it right, congratulations!" << endl;
    
    return 0;
}				/* ----------  end of function main  ---------- */

// February 15, 2017
// Request a letter from the alphabet from the user and make sure
// that the user gives us a letter. If it's not, display an error
// message. If it is , display the letter.
#include <iostream>

using namespace std;

int main()
{
  char input;
  
  cout << "Please enter any letter of the alphabet" << endl;
  cin >> input;
  
  if ((input >= 65 && input <= 90) || (input >= 97 && input <= 122))
    cout << "your letter is " << input << endl;
  else
    cout << "This is not a letter" << endl;
  
  
  return 0;
}


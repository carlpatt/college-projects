#include <iostream>
#include <string>
using namespace std;

struct FavGame { 
    string gameName;
    int releaseYear;
};

int main() {
    
    FavGame g1;

   // write the statement to read game information here
    cout << "Enter the name of your favourite game" << endl;
    getline(cin, g1.gameName);
    cout << "Now enter its release year" << endl;
    cin >> g1.releaseYear;
   // write statement to display game information
    cout << "Your favourite game is " << g1.gameName;
    cout << " and its release date is " << g1.releaseYear << endl;
   return 0;
}

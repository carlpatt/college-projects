#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

bool is_prime(int k) {
    //Returns true if "int k" is prime
    if (k < 2) return false;
    for (int i = 2; i <= static_cast<int> (sqrt(k)); i++)
        if (k % i == 0)
            return false;
    return true;
}

int main() {

    //create and populate the vector
    vector<int> vector1(1000);
    for(int x = 0; x < 1000; x++) {
        vector1.at(x) = x + 1;
    }

    int range1, range2, range3, range4;

    //Counts the number of primes and stores in count
    int count = 0;
    for(int i = 0; i < vector1.size(); i++) {
        if(is_prime(vector1.at(i)) && (i < 249)) {
            range1 += 1;
        }
    }
    cout << range1 << endl;
    return 0;
}
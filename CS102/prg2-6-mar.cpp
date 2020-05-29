/*
 * =====================================================================================
 *
 *       Filename:  prg2-6-mar.cpp
 *
 *    Description:  Write a program that request an integer from the user. If the int is
 *                  less than 20, have the program print "hello" 20 times.
 *
 *        Version:  1.0
 *        Created:  03/06/2017 09:58:47 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (Carl Patterson), 
 *   Organization:  LIU Brooklyn
 *
 * =====================================================================================
 */

#include <iostream>


using namespace std;

int main() {

    int user_int;

    cout << "Please enter an integer" << endl;
    cin >> user_int;

    if (user_int < 20) {
        for (int i =1; i < 21; i++) {

            cout << i << ": Hello." << endl;
        }
    }


    return 0;
}

#include "Member.h"
#include <iostream>
#include <string>

using namespace std;

Member::Member(string name, int age, string membershipID, string borrowedBooks[]){
    name = name;
    age = age;
    membershipID = membershipID;
    borrowedBooks = borrowedBooks;
}

string menuInput(){
    string input = "";
    cout << "Please select a number for the option of: " << endl;
    cout << "1- Login" << endl << "2- Register" << endl;
    cout << "3- Borrow a book" << endl << "4- Exit" << endl;
    cout << "Option: " << endl;
    //Taking the string input which represents the choice that the user has made
    while (input != "1" && input != "2" && input != "3" && input != "4") cin >> input;
    return input;
}

int main(){
    string choice = menuInput();
    switch(choice){
        case "1":
            //Logging in as a user
                //Prompt them to enter a membershipID and a password
                //Make sure that we find a match in the .txt file
                    //If so, create a Member() object for this person and print out their details except their password
            break;
        case "2":
            //Registering a new user
            break;
        case "3":
            //Borrowing a book
            break;
        case "4":
            break;  
    }
}
#include "Member.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

Member::Member(string name, int age, string membershipID, string borrowedBooks[]){
    name = name;
    age = age;
    membershipID = membershipID;
    borrowedBooks = borrowedBooks;
}

char menuInput(){
    char input;
    cout << "Please select a number for the option of: " << endl;
    cout << "1- Login" << endl << "2- Register" << endl;
    cout << "3- Borrow a book" << endl << "4- Exit" << endl;
    cout << "Option: " << endl;
    //Taking the string input which represents the choice that the user has made
    while (input != '1' && input != '2' && input != '3' && input != '4') cin >> input;
    return input;
}

Member findMember(string &memberID, string &password){
    ifstream reader("memberships.txt");

    //Should return the new Line storing all of the values of this string
    string newline = "";
    getline(reader, newline);
    if(!reader.eof()){
        //Split the string into an array of strings, separating each string with commas like a CSV file
        stringstream memberDetails(newline);
        string membershipID = " ";
        string thisPassword = " "; // temporary string to store split string
        //This skips to the third value in the string separated by the comma delimiter
        for(int i=0;i<3;i++) getline(memberDetails, membershipID, ",");

        //Now, we should compare if this membershipID is equal to the one inputted by the user
        if(memberID == membershipID){
            //We get the password which should be after the membershipID stored in the file
            getline(memberDetails, thisPassword, ",");
            if(password == thisPassword){
                //Cool, this is our member
                //Now, let's get all of their data from this string and store it in a Member object
                memberDetails.clear(); //Clears and empties the data stored in memberDetails - could be optimised later on perhaps
                stringstream foundMemberDetails(newline);
                string basicValues[3]; //I will store the name, age and membershipID in this
                string tempString = "";
                for(int i=0;i<3;i++){
                    getline(foundMemberDetails, basicValues[i], ",");
                }
                //This is the password which we aren't storing
                getline(foundMemberDetails, tempString, ",");

                //From this point onwards, we should just be fetching the borrowed books of this user
                int arrayLength = 0;
                string borrowedBooks[10]; //Could use arraycpy() to double array size when threatened to fill up completely
                //Use an arraycpy to copy values into a smaller array of the right size;
                while(getline(foundMemberDetails, tempString, ",")){
                    borrowedBooks[arrayLength++] = tempString;
                }

                //stoi converts strings to integers
                Member foundMember = new Member(basicValues[0], stoi(basicValues[1]), basicValues[2], thisPassword, borrowedBooks);
                return foundMember;
            }
        }
    }
    //If we fail to find the member, then I'll return an empty Member with no defined variables
    Member emptyBoi = new Member();
    return emptyBoi;
}

int main(){
    ofstream UserDataBase("memberships.txt");
    char choice = menuInput();
    switch(choice){
        case "1":
            //Logging in as a user
                //Prompt them to enter a membershipID and a password
            string membershipID;
            string password;
            cout << "Please enter your membershipID: ";
            cin >> membershipID;
            cout << endl << "Please enter your password: ";
            cin >> password;
            //Make sure that we find a match in the .txt file
                //Could maybe return an empty Member object if we fail to find this user
            Member returningUser = findMember(membershipID, password);
            //Print a "Welcome message first"
            cout << "Welcome " << returningUser.getName() << "!" << endl;
            //Then print out the object
            cout << returningUser;
            break;
        case "2":
            //Registering a new user
            string name;
            string membershipID;
            string password;
            int age;
            int booksToBorrow = 0;
            //Get the user's information here
            cout << "Please enter your name: ";
            cin >> name;

            cout << endl << "Please enter your age: ";
            cin >> age; 

            cout << endl << "Please enter your 6-digit membership ID: ";
            cin >> membershipID;

            cout << endl << "Please enter your password: ";
            cin >> password;

            cout << "Please tell us how many books you are going to borrow initially? ";
            cin >> booksToBorrow;
            //Dynamically creating an array of size booksToBorrow
            string* borrowedBooks = new string[booksToBorrow];
            //As I know the number of books which they are borrowing, I could theoretically also store this in the Member object
            UserDataBase << name << "," << age << "," << membershipID << "," << password;
            for(int i=0;i<booksToBorrow<i++){
                string bookName;
                string bookAuthor;
                //Ask them for the name of the book to borrow
                cout << "Please enter the name of the book you are borrowing: ";
                cin >> bookName;
                cout << endl << "Please enter the author of this book: ";
                cin >> bookAuthor;
                    //Could ask them first for the book name and user the \" to show the quotations around it
                    //Then ask them for the author and stick a "by" in-between them for nice visualisation
                //Replace this space placeholder with that name of the book
                UserDataBase << "," << "\"" << bookName << "\"" << " by " << bookAuthor; 
            }
            UserDataBase << endl; //This should signify to the program that this is all of the data for this user
            break;
        case "3":
            //Borrowing a book
            break;
        case "4":
            exit();  
    }
}
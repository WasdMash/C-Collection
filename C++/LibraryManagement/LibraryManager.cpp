#include "Member.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <cstdio>

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

                foundMemberDetails.close();
                //stoi converts strings to integers
                Member foundMember = new Member(basicValues[0], stoi(basicValues[1]), basicValues[2], thisPassword, borrowedBooks);
                return foundMember;
            }
        }
    }
    reader.close();
    //If we fail to find the member, then I'll return an empty Member with no defined variables
    Member emptyBoi = new Member();
    return emptyBoi;
}

int main(){
    ofstream UserDataBase("memberships.txt");
    bool loggedIn = false;
    string loggedUserId;
    string loggedPassword;
    string bookName;
    string bookAuthor;
    char choice = menuInput();

    while(choice != '4'){
        if(!UserDataBase) ofstream UserDataBase("memberships.txt");
        switch(choice){
        case "1":
            //Logging in as a user
                //Prompt them to enter a membershipID and a password
            cout << "Please enter your membershipID: ";
            cin >> loggedUserId;
            cout << endl << "Please enter your password: ";
            cin >> loggedPassword;
            //Make sure that we find a match in the .txt file
                //Could maybe return an empty Member object if we fail to find this user
            Member returningUser = findMember(loggedUserId, loggedPassword);
            //Print a "Welcome message first"
            cout << "Welcome " << returningUser.getName() << "!" << endl;
            //Then print out the object
            cout << returningUser;

            //Resets getline() to start from the top
            UserDataBase.seekg(0);
            break;
        case "2":
            //Registering a new user
            string name;
            int age;
            int booksToBorrow = 0;
            int booksBorrowed = 0;
            //Get the user's information here
            cout << "Please enter your name: ";
            cin >> name;

            cout << endl << "Please enter your age: ";
            cin >> age; 

            cout << endl << "Please enter your 6-digit membership ID: ";
            cin >> loggedUserId;

            cout << endl << "Please enter your password: ";
            cin >> loggedPassword;

            cout << endl << "Please tell us how many books you want to borrow? ";
            cin >> booksToBorrow;
            //I might also want to ask how many books they want to initially borrow and leave empty spaces in the rest
                //If I really cared, I would validate to make sure that this number is less than booksToBorrow
            cout << endl << "How many of these books will you borrow now? ";
            cin >> booksBorrowed;

            //Dynamically creating an array of size booksToBorrow
            string* borrowedBooks = new string[booksToBorrow];
            //As I know the number of books which they are borrowing, I could theoretically also store this in the Member object
            UserDataBase << name << "," << age << "," << loggedUserId << "," << loggedPassword;
            for(int i=0;i<booksToBorrow<i++){
                //Handles the books which the user is immediately borrowing
                if(i < borrowedBooks){
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
                else{
                    //Handles the books which they are able to borrow in the future
                    UserDataBase << ", ";
                }
                 
            }
            UserDataBase << endl; //This should signify to the program that this is all of the data for this user

            //Resets getline() to start from the top
            UserDataBase.seekg(0);
            break;
        case "3":
            //Borrowing a book
            //Use s.find to find the first " " in the string
                //This will indicate the first gap where the user can borrow another book

            cout << "Please enter the name of the book you are borrowing: ";
            cin >> bookName;
            cout << endl << "Please enter the author of this book: ";
            cin >> bookAuthor;

            bool foundUser = false;
            int lineToReplace = 0;
            string tempString = "";
            while(!foundUser){
                getline(UserDataBase, tempString);
                if(tempString.find(loggedUserId) != string::npos) break;
                //It looks like if I want to update a line, I have to manually re-write the whole thing which is really annoying
                lineToReplace++;
            }
            foundUser = true;

            //Resets getline() to start from the top
            UserDataBase.seekg(0);

            //Basically loop lineToReplace times, copying the old line into a string
            ifstream ReadMemberInfo("memberships.txt");
            ofstream TempDataStore("tempFile.txt");
            int i=0;
            while(getline(ReadMemberInfo,tempString)){
                //Should double check to make sure that I don't accidentally insert this inside a book name
                if(i==lineToReplace){
                    tempString.insert(tempString.find(", "), "\"" + bookName + "\" by " + bookAuthor);
                }
                TempDataStore << tempString;
                i++;
            }
            //I can't be bothered to copy everything back into the original so I'll just delete the old file and rename the new one to cut corners
            remove("memberships.txt");
            rename("tempFile.txt","memberships.txt");
            
            break;
    }
    //The user is clearly finished with the program, so let's cleanly close all of the pipes

    UserDataBase.close();
    exit();  
    }
}
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

string findMember(ofstream &textFile, string &memberID, string &password){
    //Should return the newLine storing all of the values of this string
    string newline = "";
    getline(textFile, newline);
    if(!textFile.eof()){
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
                sting tempString = "";
                for(int i=0;i<3;i++){
                    getline(foundMemberDetails, basicValues[i], ",");
                }
                //This is the password which we aren't storing
                getline(foundMemberDetails, tempString, ",");
            }
        }
    }
}

int main(){
    ofstream UserDataBase("memberships.txt");
    //I'm thinking of storing the details of each member in a single line in a CSV format
    //Need to figure out how to split values using a delimiter
        //This link could be helpful: https://www.geeksforgeeks.org/how-to-split-string-by-delimiter-in-cpp/
        /*Could also store books on this line and check for the total
         number of books by looking at the length of the array past 3 - 
         0-3 store the name, age, ID and password of the user*/
    string choice = menuInput();
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
            
            //Print out all of the details of this member object as shown in the PDF
            break;
        case "2":
            //Registering a new user
            string name;
            string membershipID;
            string password;
            string[] borrowedBooks; 
            int age;
            cout << "Please enter your name: ";
            cin >> name;
            cout << endl << "Please enter your age: ";
            cin >> age;
            cout << endl << "Please enter your 6-digit membership ID: ";
            cin >> membershipID;
            cin << endl << "Please enter your password";
            cin >> password;
            UserDataBase << name << "," << to_string(age) << "," << membershipID << "," << password << ",";
            //Don't forget to ask the user which books they would want to borrow
                //Store that in the line as well
            break;
        case "3":
            //Borrowing a book
            break;
        case "4":
            break;  
    }
}
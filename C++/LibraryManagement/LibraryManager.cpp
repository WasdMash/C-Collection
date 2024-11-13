#include "Member.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

Member::Member(string name, int age, string membershipID, vector<string> borrowedBooks){
    name = name;
    age = age;
    membershipID = membershipID;
    borrowedBooks = borrowedBooks;
}

ostream& operator<<(ostream &os, const Member &other)
{
    os << "Your age is " << other.age << endl
    << "Your membership ID is " << other.membershipID << "." << endl << "Your borrowed books are: " << endl;

    if(other.borrowedBooks.size() != 0){
        for(int i=0;i<other.borrowedBooks.size();i++){
            //Could come back to this later to manually add the quotation marks to the book titles
            os << " - " << other.borrowedBooks[i] << endl;
        }
    }

    return os;
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
    string newline;
    getline(reader, newline);
    if(!reader.eof()){
        //Split the string into an array of strings, separating each string with commas like a CSV file
        string del = ",";
        string userInfo = newline;
        string thisPassword;

        //Apparently, I can't use getline on a stringstream so I'll need another way to split a string using ,
        auto pos = userInfo.find(del);
        //This loop should fetch the string starting with the membershipID
        for(int i=0;i<2;i++){
            userInfo.erase(0, pos+del.length());
            pos = userInfo.find(del); 
        }

        //Now, we should compare if this membershipID is equal to the one inputted by the user
        if(memberID == userInfo.substr(0,pos)){
            //We get the password which should be after the membershipID stored in the file
            userInfo.erase(0, pos+del.length());
            pos = userInfo.find(del);

            if(password == userInfo.substr(0,pos)){
                //Cool, this is our member
                //Now, let's get all of their data from this string and store it in a Member object

                string basicValues[3]; //I will store the name, age and membershipID in this
                for(int i=0;i<3;i++){
                    basicValues[i] = newline.substr(0,pos);
                    newline.erase(0, pos+del.length());
                    pos = newline.find(del); 
                }

                //This is the password which we aren't storing
                newline.erase(0, pos+del.length());
                pos = newline.find(del);

                //From this point onwards, we should just be fetching the borrowed books of this user
                vector<string> borrowedBooks; 

                while(pos != string::npos){
                    borrowedBooks.push_back(newline.substr(0,pos));
                    newline.erase(0, pos+del.length());
                    pos = newline.find(del);
                }

                //stoi converts strings to integers
                //OStream requires a static object, not a dynamically ccreated one
                Member foundMember(basicValues[0], stoi(basicValues[1]), basicValues[2], borrowedBooks);
                return foundMember;
            }
        }
    }
    reader.close();
    //If we fail to find the member, then I'll return an empty Member with no defined variables
    Member emptyBoi("ERROR",-12,"ERROR", vector<string>(1," "));
    return emptyBoi;
}

int main(){
    ofstream UserDataBase("memberships.txt");
    ifstream ReadMemberInfo("memberships.txt");
    
    bool loggedIn = false;
    string loggedUserId;
    string loggedPassword;
    string bookName;
    string bookAuthor;
    char choice = menuInput();

    while(choice != '4'){
        if(!UserDataBase) ofstream UserDataBase("memberships.txt");
        if(ReadMemberInfo) ifstream ReadMemberInfo("memberships.txt");
        if(choice == '1'){
            //Logging in as a user
                //Prompt them to enter a membershipID and a password
            cout << "Please enter your membershipID: ";
            cin >> loggedUserId;
            cout << endl << "Please enter your password: ";
            cin >> loggedPassword;
            //Make sure that we find a match in the .txt file
                //Could maybe return an empty Member object if we fail to find this user
            Member returningUser = findMember(loggedUserId, loggedPassword);
            if(returningUser.getName() != "ERROR"){
                //Print a "Welcome message first"
                cout << "Welcome " << returningUser.getName() << "!" << endl;
                //Then print out the object
                cout << returningUser;
            }
            else{
                cout << "User is not found in our system. I'd recommend that you create a new account." << endl;
            }

            //Resets getline() to start from the top
            UserDataBase.close();
        }
        else if(choice == '2'){
            //Registering a new user
            string name;
            int age;
            int booksToBorrow = 0;
            int booksBorrowed = 0;
            //Get the user's information here
                //Bruh - cin only reads up to the first whitespace - why?!
                //Why do I have to use getline to get the full string, man?
            cout << "Please enter your name: ";
            getline(cin,name);

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

            //As I know the number of books which they are borrowing, I could theoretically also store this in the Member object
            UserDataBase << name << "," << age << "," << loggedUserId << "," << loggedPassword;
            for(int i=0;i<booksToBorrow;i++){
                //Handles the books which the user is immediately borrowing
                if(i < booksBorrowed){
                    //Ask them for the name of the book to borrow
                    cout << "Please enter the name of the book you are borrowing: ";
                    getline(cin,bookName);
                    cout << endl << "Please enter the author of this book: ";
                    getline(cin,bookAuthor);
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
            UserDataBase.close();
        }
        else if(choice == '3'){
            //Borrowing a book
            //Use s.find to find the first " " in the string
                //This will indicate the first gap where the user can borrow another book

            cout << "Please enter the name of the book you are borrowing: ";
            getline(cin,bookName);
            cout << endl << "Please enter the author of this book: ";
            getline(cin,bookAuthor);

            bool foundUser = false;
            int lineToReplace = 0;
            string tempString;

            while(!foundUser){
                getline(ReadMemberInfo, tempString);
                if(tempString.find(loggedUserId) != string::npos) break;
                //It looks like if I want to update a line, I have to manually re-write the whole thing which is really annoying
                lineToReplace++;
            }
            foundUser = true;

            //Resets getline() to start from the top
            ReadMemberInfo.close();

            //Basically loop lineToReplace times, copying the old line into a string
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
        }
    }
    //The user is clearly finished with the program, so let's cleanly close all of the pipes

    UserDataBase.close();
    abort();  
}
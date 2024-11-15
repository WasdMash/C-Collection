#include "Member.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

Member::Member(string name, int age, string membershipID, vector<string> borrowedBooks){
    //Don't forget the 'this' keyword, otherwise the compiler will fail to tell where to assign the values
    this->name = name;
    this->age = age;
    this->membershipID = membershipID;
    this->borrowedBooks = borrowedBooks;
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

string encrypt(string msg, string key)
{
    // Make sure the key is at least as long as the message
    string tmp(key);
    while (key.size() < msg.size())
        key += tmp;
    
    // And now for the encryption part
    for (string::size_type i = 0; i < msg.size(); ++i)
        msg[i] ^= key[i];
    return msg;
}
string decrypt(string msg, string key)
{
    return encrypt(msg, key); // lol
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
    reader.clear();

    while(!reader.eof()){
        //Split the string into an array of strings, separating each string with commas like a CSV file
        string del = ",";
        string userInfo;
        string thisPassword;

        //Should return the new Line storing all of the values of this string
        getline(reader, userInfo);
        int startPos = 0;
        size_t pos = 0;
        //This loop should fetch the string starting with the membershipID
        for(int i=0;i<2;i++){
            pos = userInfo.find(del, startPos);
            startPos = pos+1;
        }

        //Now, we should compare if this membershipID is equal to the one inputted by the user
        pos = userInfo.find(del, startPos);

        if(memberID == userInfo.substr(startPos,pos-startPos)){
            //We get the password which should be after the membershipID stored in the file
            
            pos = userInfo.find(del, startPos);
            startPos = pos+1;
            pos = userInfo.find(del, startPos);

            if(password == userInfo.substr(startPos,pos-startPos)){
                //Cool, this is our member
                //Now, let's get all of their data from this string and store it in a Member object

                string basicValues[3]; //I will store the name, age and membershipID in this
                startPos = 0;
                auto pos = 0;

                for(int i=0;i<3;i++){
                    pos = userInfo.find(del, startPos);
                    basicValues[i] = userInfo.substr(startPos,pos-startPos);
                    cout << basicValues[i] << endl;
                    startPos = pos+1;
                }

                //This is the password which we aren't storing
                pos = userInfo.find(del, startPos+1);
                startPos = pos+1;

                //From this point onwards, we should just be fetching the borrowed books of this user
                vector<string> borrowedBooks; 

                while(pos != string::npos){
                    pos = userInfo.find(del, startPos+1);
                    borrowedBooks.push_back(userInfo.substr(startPos,pos-startPos));
                    startPos = pos+1;
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
    //Apparently, this overwrites the file if it already exists
    ofstream UserDataBase;
    //This second line is very important to prevent overwrites
    UserDataBase.open("memberships.txt",ios::app);
    ifstream ReadMemberInfo("memberships.txt");
    
    string *loggedUserId = new string;
    string *loggedPassword = new string;
    string *bookName = new string;
    string *bookAuthor = new string;
    char *choice = new char; //Placeholder value to get loop going
    *choice = 'N';

    while(*choice != '4'){
        *choice = menuInput();

        if(!UserDataBase){
            UserDataBase.open("memberships.txt",ios::app);
        }
        if(!ReadMemberInfo) ifstream ReadMemberInfo("memberships.txt");
        if(*choice == '1'){
            //Logging in as a user
                //Prompt them to enter a membershipID and a password

            //Should use a while loop to keep asking them to enter a valid format
                //Starts with a 'M' and is followed by 6 digits    
            cout << "Please enter your membershipID: ";
            cin >> *loggedUserId;
            //Should probably encrypt and decrypt this password so that it isn't visible
            cout << "Please enter your password: ";
            cin >> *loggedPassword;
            //Make sure that we find a match in the .txt file
                //Could maybe return an empty Member object if we fail to find this user
            Member returningUser = findMember(*loggedUserId, encrypt(*loggedPassword, *loggedUserId));
            if(returningUser.getName() != "ERROR"){
                //Print a "Welcome message first"
                cout << "Welcome " << returningUser.getName() << "!" << endl;
                //Then print out the object
                cout << returningUser << endl;
            }
            else{
                cout << endl << "User is not found in our system. I'd recommend that you create a new account." << endl << endl;
            }

            //Resets getline() to start from the top
            UserDataBase.close();
        }
        else if(*choice == '2'){
            //Registering a new user
            string *name = new string; 
            int *age = new int(0);
            int *booksToBorrow = new int(0);
            int *booksBorrowed = new int(0);
            //Get the user's information here
                //Bruh - cin only reads up to the first whitespace - why?!
        
            cout << "Please enter your name: ";
            getline(cin,*name);
            getline(cin,*name);

            cout << "Please enter your age: ";
            cin >> *age; 

            cout << "Please enter your 6-digit membership ID: ";
            cin >> *loggedUserId;

            cout << "Please enter your password: ";
            cin >> *loggedPassword;

            cout << "Please tell us how many books you want to borrow? ";
            cin >> *booksToBorrow;

            //As I know the number of books which they are borrowing, I could theoretically also store this in the Member object

            //Quick check if the file is empty
            ReadMemberInfo.seekg(0, ios::end);
            if(ReadMemberInfo.tellg() == 0) UserDataBase << endl;
            ReadMemberInfo.clear();
            ReadMemberInfo.close();

            UserDataBase << *name << "," << *age << "," << *loggedUserId << "," << encrypt(*loggedPassword, *loggedUserId);
            for(int i=0;i<*booksToBorrow;i++){
            //Handles the books which the user is immediately borrowing
                //Ask them for the name of the book to borrow
                cout << "Please enter the name of the book you are borrowing: ";
                //Just to counteracct the extra /n left behind by using the cin
                if(i==0) getline(cin,*bookName);
                getline(cin,*bookName);

                cout << endl << "Please enter the author of this book: ";
                getline(cin,*bookAuthor);
                    //Could ask them first for the book name and user the \" to show the quotations around it
                    //Then ask them for the author and stick a "by" in-between them for nice visualisation
                //Replace this space placeholder with that name of the book
                UserDataBase << "," << "\"" << *bookName << "\"" << " by " << *bookAuthor;  
            }

            //Resets getline() to start from the top
            UserDataBase.close();

            //Garbage collecting the heap stuff which aren't being used anymore
            delete name;
            delete booksToBorrow;
            delete age;
        }
        else if(*choice == '3'){
            //Borrowing a book

            //Don't forget to prompt the user to log out if they are logged into someone else's account
            cout << endl << "If this isn't your membership ID, you might want to restart the program and login to borrow a book for yourself." << endl;
            cout << "Current user: " << *loggedUserId << endl;
            char *isThisYou = new char;
            *isThisYou = 'G';

            while(*isThisYou != 'Y' && *isThisYou != 'N'){
                cout << "Is this your account? Press \'Y\' for yes and \'N\' for no:";
                cin >> *isThisYou;
                *isThisYou = toupper(*isThisYou);
            }
            //clearly the right user must be logged in now, otherwise, they are sent back to the main menu to login properly now
            if(*isThisYou == 'Y'){
                //Use s.find to find the first " " in the string
                //This will indicate the first gap where the user can borrow another book

                cout << "Please enter the name of the book you are borrowing: ";
                getline(cin,*bookName);
                getline(cin,*bookName);

                cout << "Please enter the author of this book: ";
                getline(cin,*bookAuthor);
 
                int *lineToReplace = new int(0);
                string *tempString = new string;
                ofstream TempDataStore("tempFile.txt");

                //This loop will loop through the file until we find the user whose details we are updating
                ReadMemberInfo.close();
                ReadMemberInfo.open("memberships.txt",ifstream::in);

                while(getline(ReadMemberInfo, *tempString)){
                    //Should double check to make sure that I don't accidentally insert this inside a book name

                    //If this is the line for this member - we found them
                    if(tempString->find(*loggedUserId) != string::npos){
                        *tempString = (*tempString) + ",\"" + *bookName + "\" by " + *bookAuthor;
                    }
                    TempDataStore << *tempString;
                    if(!ReadMemberInfo.eof()) TempDataStore << endl;
                    //It looks like if I want to update a line, I have to manually re-write the whole thing which is really annoying
                    (*lineToReplace)++;
                }

                //This isn't successfully closing the thing
                //Maybe I should close the pipe first?
                UserDataBase.close();
                ReadMemberInfo.close();
                TempDataStore.close();

                remove("memberships.txt");
                rename("tempFile.txt","memberships.txt");

                //Garbage collection time
                delete tempString;
                delete lineToReplace; delete isThisYou;

            }
            else{
                cout << endl << "You are now being sent back to the main menu to log into the right account" << endl;
            }

        }
    }
    //The user is clearly finished with the program, so let's cleanly close all of the pipes
    //Let's also clear all of the heap variables
    delete choice;
    delete bookAuthor; delete bookName;
    delete loggedPassword; delete loggedUserId;

    if(UserDataBase) UserDataBase.close();
    abort();  
}
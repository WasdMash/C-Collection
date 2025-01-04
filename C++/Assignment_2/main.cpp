#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "User.h"
#include "Manager.h"
#include "ReadPost.h"

using namespace std;

// Exception classes
class WrongFileFormatException : public exception {
public:
    const char *what() const throw() {
        return "Unable to successfully process the information of this user in the text file.";
    }
};

class UserDontExistException : public exception {
private:
    string username;

public:
    UserDontExistException(const string &username) : username(username) {}

    const char *what() const throw() {
        string message = username + " doesn't yet exist in our database, so let's add you then.";
        return message.c_str();
    }
};

// Global variables
string postFileName = "Post_database.txt";
string blacklistName = "blacklist.txt";

// Template function for login
template <class T>
T login(string &username, ReadPosts& postManager) {
    ifstream userFile("users.txt");
    if (!userFile) {
        throw WrongFileFormatException();
    }

    string line;
    string *managerName = new string;
    int *managerID = new int;
    while (getline(userFile, line)) {
        stringstream ss(line);
        int regNo;
        string name, surname;

        ss >> regNo >> name >> surname;
        string fullName = name + " " + surname;

        if (to_string(regNo).length() == 9) {
            // User
            User newUser(fullName, regNo);
            postManager.addUser(newUser);
        } else if (to_string(regNo).length() == 4) {
            // Manager
            
            if(tolower(fullName) == tolower(username)){
                //Wait first before returning
                *managerName = fullName;
                *managerID = regNo;
            }
        } else {
            throw WrongFileFormatException();
        }
    }

    //Let's check if our manager exists
    if(strlen(*managerName) > 0){
        //Then, our manager exists and we should return him
        Manager newManager(*managerName, *managerID);
        return newManager;
    }

    //If not, then let's delete the dynamic variables
    delete managerName; delete managerID;
    
    //Now let's check to see if any of these users is what we are looking for
        //Should probably update each of their score first before we return any of them
    for(vector<User>::iterator it = postManager.getUsers().begin(); it != postManager.getUsers().end(); it++){
        if(it->getName() == username){
            return *it;
        }
    }
    

    //If we haven't found them to be either a user or manager, then throw an appropiate exception
    throw UserDontExistException(username);
}

void printUser(User& currentUser){
    cout << currentUser << endl;
}

void updateUserDatabase(ReadPosts &postManager){
    ifstream oldUserDataBase("users.txt"); //This is the current file
    ofstream newUserDatabase("temp.txt"); //This'll be the new database

    if(oldUserDataBase){
        string *currentLine = new string;
        while(getline(oldUserDataBase, *currentLine)){
            if(strlen(*currentLine) > 1){
                //Should by default copy all managers from the old to the new
                string *ID = new string;
                stringstream currentLineSS(*currentLine);
                currentLineSS >> *ID;
                //If the ID is 4 digits, then it's a manager and we'll copy their details to the new file
                    //Otherwise, we'll skip it for now and add the user info from the program to the file afterwards
                if(strlen(*ID) == 4){
                    //We have found a manager's details to copy to the new file
                    newUserDatabase << *currentLine;
                }
                delete ID;
            }

        }
        //Now, let's get the info of each user from the iterable container and write them to this new file
        for(vector<User>::iterator it = postManager.getUsers().begin(); it != postManager.getUsers().end(); it++){
            //I want to write each user's information to the file
            newUserDatabase << it->writeToFile() << endl;
        }

        oldUserDataBase.close();
        newUserDatabase.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
    }
    else{
        cout << "The users database doesn't exist in this directory" << endl;
    }
}

// User options menu
void userOptions(User &currentUser, ReadPosts& postManager) {
    int choice = 0;
    
    while (choice != 5) {
        cout << "User Options:\n"
             << "1. Read post\n"
             << "2. Write a post\n"
             << "3. View your statistics\n"
             << "4. Display top 10 most problematic users\n"
             << "5. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            string *readingPostChoice = new string;
            while(*readingPostChoice != "1" && *readingPostChoice != "2" && *readingPostChoice != "3"){
                //Should actually return the index to this post from ReadPosts so that we can change its reputation score
                pair<string, string> postContent = postManager.findPost();
                cout << postContent.second << endl;

                //Presenting the choices to the user
                cout << "Reading post Options:\n"
                    << "1. Read another post\n"
                    << "2. Report this post\n"
                    << "3. Go back to the main menu\n";
                cin >> *readingPostChoice;

                if(*readingPostChoice == "1") cout << "Fetching new post now..." << endl << endl;
                if(*readingPostChoice == "2"){
                    //The post is getting reported and the user who posted it will be punished
                    vector<User> userVector = postManager.getUsers();
                    for(vector<User>::iterator it = userVector.begin(); it != userVector.end(); it++){
                        if(it->getRegNo() == stoi(postContent.first)){
                            //This is the user whose post is getting reported
                            //Then also update the reputation score of that user
                            it->loseReputation(postContent.second, 10); //it should be -10 per reported post
                            it->updateScores();
                            updateUserDatabase(postManager);
                            break;
                        }
                    }
                }
                if(*readingPostChoice == "3"){
                    cout << "Exiting the program now" << endl;
                    break; //Should take the user back to the main menu
                }
                else cout << "Invalid option. Please only enter values between 1 and 3, thank you" << endl;
            }
                
        }
        case 2: {
            string newPost = "";
            
            while(strlen(newPost) < 1 && strlen(newPost) > 140){
                cout << "Write your post (max 140 characters): ";
                cin.ignore();
                getline(cin, newPost);
            }

            //Should probably around this point run the moderation function on this text
            pair<string, string> addedPost =  postManager.addPost(currentUser.getRegNo(), newPost);
            currentUser.addScore(100, addedPost.second); //The default score for each post should be 100 before moderation
            postManager.moderatePost(addedPost, blacklistName, postFileName);
            postManager.updateTextFile();
            
            currentUser.updateScores(); //Doesn't exist yet
            //Now, I should take the values from this current user and use them to update the values in the text file
            updateUserDatabase(postManager);

            break;
        }
        case 3:
            cout << currentUser << endl;
            break;
        case 4:
            // Display top 10 problematic users
            vector<User> filteredUsers;
            vector<User>::iterator tempIt; //Temp iterator used to copy valid users into filteredUsers
            
            for(tempIt = postManager.getUsers().begin(); tempIt != postManager.getUsers.end(); tempIt++){
                if(tempIt->getReputation() >= 0){
                    filteredUsers.push_back(*tempIt); //Add this valid user to the filteredUsers to be used later
                }
            }
            sort(filteredUsers.begin(), filteredUsers.end());
            //I need to use for_each each to print out the details of each of the users here
            for_each(filteredUsers.begin(), filteredUsers.end(), printUser);
            break;
        case 5:
            cout << "Goodbye!" << endl;
            exit(1);
            return;
        default:
            cout << "Invalid option. Try again." << endl;
        }
    }
}

// Manager options menu
void managerOptions(Manager &currentManager, ReadPosts& postManager) {
    int choice = 0;

    while (choice != 5) {
        cout << "Manager Options:\n"
             << "1. Reset moderation content\n"
             << "2. Add blocked content\n"
             << "3. Add another manager\n"
             << "4. Set the sample file\n"
             << "5. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            ofstream blacklistFile(blacklistName, ios::trunc);
            cout << "Blocked content reset." << endl;
            //I should probably reset all scores to be 100 if there's nothing moderated rn
            for(vector<User>::iterator it = postManager.getUsers().begin(); it != postManager.getUsers().end(); it++){
                //I want to write each user's information to the file
                it->resetModeration();
            }
            break;
        }
        case 2: {
            ofstream blacklistFile(blacklistName, ios::app);
            string blockedWord;
            cout << "Enter a word/phrase to block: ";
            cin.ignore();
            getline(cin, blockedWord);
            blacklistFile << blockedWord << endl;

            //I should automatically be moderating all of the posts
            postManager.moderateAllPosts(blacklistName, postFileName);
            break;
        }
        case 3: {
            string newManagerName;
            int newManagerID;
            cout << "Enter new manager name: ";
            cin.ignore();
            getline(cin, newManagerName);
            //ID verification
            while(newManagerID < 1000 && newManagerID > 10000){
                cout << "Enter new manager ID (4 digits): ";
                cin >> newManagerID;
            }
            ofstream userFile("users.txt", ios::app);
            userFile << newManagerID << " " << newManagerName << endl;
            break;
        }
        case 4:
            cout << "Enter new post file name: ";
            cin >> postFileName;
            if(postFileName.substr(strlen(postFileName)-4), 4 != ".txt"){
                postFileName.append(".txt"); //Adding the text file extension to the end in case the manager forgot to do so
            }
            break;
        case 5:
            cout << "Goodbye!" << endl;
            exit(1);
        default:
            cout << "Invalid option. Try again." << endl;
        }
    }
}

int main() {
    string username;
    cout << "Enter your username: ";
    cin >> username;
    ReadPosts postManager(postFileName.c_str());
    try{
        postManager.readAllPosts();
    }
    catch(...){
        cout << postFileName << " doesn't exist and so this program can't do much now, so bye bye" << end;
        exit(1);
    }

    try {
        auto user = login<Person>(username, postManager);
        //Should check down here if user is a user or a manager
        if(user.getRegNo() < 10000){
            //Must be a manager then
            managerOptions(user, postManager);
        }
        else if(user.getRegNo() < 10000000000 && user.getRegNo() > 1000000000){
            //The reg ID should be 9 digits, which is a user's ID
            userOptions(user, postManager);
        }
        
    } catch (const UserDontExistException &e) {
        cout << e.what() << endl;
        //This is where we should create the new user which doesn't exist yet
        string *newUserId = new string;
        while(strlen(*newUserId) != 9){
            cout << "Enter new user ID (9 digits): ";
            cin.ignore();
            getline(cin, *newUserId);
            cin >> *newUserId;
        }
        //Adding this new user to the file
        ofstream userFile("users.txt", ios::app);
        userFile << username << " " << *newUserId << endl;

        User user = login<Person>(username, postManager);
        userOptions(user, postManager);
        
        delete newUserId;

    } catch (const WrongFileFormatException &e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "An unknown error occurred." << endl;
    }

    return 0;
}

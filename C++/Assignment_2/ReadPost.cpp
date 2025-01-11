#include "ReadPost.h"
#include <iostream>
#include <algorithm>  // for distance and advance if needed
#include <cstdlib>    // for rand(), srand()
#include <ctime>      // for time()
#include <sstream>    // for parsing lines
#include <cctype>

using namespace std;

ReadPosts::ReadPosts(const char *filename)
{
    postfile.open(filename);
    if (!postfile)
    {
        cerr << "Failed to open " << filename << endl;
        exit(1); // Terminate if file cannot be opened
    }

    // Optionally seed the random number generator
    srand(static_cast<unsigned>(time(NULL)));
}

void ReadPosts::close()
{
    if (postfile.is_open())
    {
        postfile.close();
    }
}

void ReadPosts::readAllPosts()
{
    //to be implemented by you
    // Expected format per line:
    // userID postID post_content date/time
    // e.g.:
    // user123 456 Hello_world! 2024-01-12T12:34:56
    //
    // Adjust parsing if your data differs. Here we assume no spaces in post_content.
    // Insert all posts from file into multimap
    string currentLine,  cur_userID, cur_user_post;
    
    while(getline(postfile, currentLine)){
        //Split this getline using a space delimiter of some sorts
        //To insert into the multimap, I just need the userID and then post content
        stringstream currentLineSS(currentLine);
        getline(currentLineSS, cur_userID, '\t'); //Gets the user ID first from this line
        getline(currentLineSS, cur_user_post, ' '); //Dummy getline to skip the post ID
        getline(currentLineSS, cur_user_post); //Need to get the rest of the line and cut off when we first encounter a digit
            //If we see a digit, then we have clearly managed to get the post content

        int *postContentEnd = new int;
        for(int i=0;i<cur_user_post.length();i++){
            if(isdigit(cur_user_post[i])){
                *postContentEnd = i - 1; //Want to cut off the space/tab before this too
                break;
            }
        }
        cur_user_post = cur_user_post.substr(0, *postContentEnd);    
        //Actually inserting this post into the multi-map
        posts.insert(pair<string,string>(cur_userID, cur_user_post));
        delete postContentEnd;
        currentLineSS.clear();

    }
}

string ReadPosts::findAuthor(const string &originalPost) const{
    multimap<string, string>::iterator ip;
    while( ip != posts.end()){
        if(ip->second.compare(originalPost) == 0){
            //We have found an exact match in our posts multimap
            return ip->first; //We should therefore return the author of this post
        }
        ip++;
    }
    //If we fail to find any such posts, then we'll return an empty string
    return "";
}

pair<string, string> ReadPosts::findPost()
{
    // to be implemented by you
    // Return the post string that is randomly found in the multimap
    int postRange = distance(posts.begin(), posts.end());
    if(postRange > 0){
        //Do stuff becaause the posts multipmap isn't empty
        int randIndex = rand() % postRange; //Should in theory return a random integer between 0 and range-1
        multimap<string, string>::iterator it = posts.begin();
        advance(it, randIndex); //Advances the it iterator by randIndex times 
        //I should return the post from this iterator which should be it->second
        return *it;
    }
    else{
        //clearly the post multimap is empty, so let's exit with grace
        cout << "The posts multimap is empty, therefore a post couldn't be returned." << endl;
        return pair<string, string>("",""); //Returning an empty string to satisfy return conditions
    }
}

string ReadPosts::getPost(const string &userID) const
{
    // to be implemented by you
    // Find posts for the given userID
    // Return the first post found for this user

    //This will be the sub-range of all posts in the multimap with a ->first value of userID
        /*
            @param posts.begin(): Forward iterator to the first element in the range.
            @param posts.end(): Forward iterator to the last element in the range.
            @param userID: Value of the subrange to search for in the range.
        */
    auto range = posts.equal_range(userID);
    for(auto it = range.first; it != range.second; it++){
        try{
            //If the string is empty, it won't trigger an error but won't be what we want
            if(it->second != "") return it->second;
        }
        catch(...){
            //If we don't even have a suitable post, just return an empty string
            return "";
        }
    }
    return "";  
}

void ReadPosts::moderatePost(const pair<string, string>& post, const string blacklistName){
    ifstream blacklist(blacklistName.c_str()); //This is the file from which we shall read all of our banned words/phrases line by line
    string *currentBadWord = new string;
    while(getline(blacklist, *currentBadWord)){
        //Fetches the current naughty word/phrase

        string *loweredPost = new string;
        for(int i=0;i<loweredPost->length();i++){
            if(isalpha((*loweredPost)[i])){
                //Only adding letters to username
                *loweredPost += tolower((*loweredPost)[i]);
            }
        }

        //Converting the current bad word to lowercase
        for(int i=0;i<currentBadWord->length();i++){
            if(isalpha((*currentBadWord)[i])){
                //Only adding letters to username
                *currentBadWord += tolower((*currentBadWord)[i]);
            }
        }

        //Check if the naughty is found within the post
        int foundBanPhrase = loweredPost->find(*currentBadWord);
        if(foundBanPhrase != string::npos){
            //We have found a bad word
            cout << foundBanPhrase << endl;
            //Don't forget to find the user with the same regNO and increment their number of moderated posts
            for(vector<User>::iterator it=users.begin(); it != users.end(); it++){
                if(to_string(it->getRegNo()) == post.first){
                    //We have found the user who triggered a moderation in their posts
                        //Therefore, let's punish them
                        it->updatedModeratedPosts();
                        int *postScore = new int;
                        if(currentBadWord->length() < 100) *postScore = currentBadWord->length();
                        else *postScore = 100;
                        
                        it->loseReputation(post.second, *postScore);
                        delete postScore;
                }
            }

            int endIndex = foundBanPhrase + currentBadWord->length(); //Need to know when to stop printing Xs
            string moderatedPost = post.second.substr(0, foundBanPhrase); //The start part of the unmoderated post before naughty word
            for(int i=0; i<currentBadWord->length(); i++){
                if((*currentBadWord)[i] != ' ') moderatedPost += "X"; //censoring the bad word here, of course
                else moderatedPost += " "; //Want to make it clear that we aren't just censoring one big word
            }
            //Adding the rest of the string back to censor only part of it
            moderatedPost += post.second.substr(endIndex, post.second.length());
            //Adding the cute #moderatedpost tag at the end
            moderatedPost += " #moderatedpost";

            //Don't forget to come back to this and update the score of this user's post
                //Would be a lot easier to do once I've made this an iterable container

            //Should updated the original post to be later updated in the text file
            const_cast<string&>(post.second) = moderatedPost;
        }
    }
    delete currentBadWord;
    //At this point, the text file should be updated accordingly
}

void ReadPosts::updateTextFile(string postFileName){
    if(!postfile.is_open()) postfile.open(postFileName.c_str());

    postfile.seekg(0); //Setting the postFile back to the beginning
    ofstream newDatabase("temp.txt"); //Temporary file to write everything into
    string *currentLine = new string;

    while(getline(postfile, *currentLine)){
        //Want to avoid errors caused by the newline character on the last line of the file
        if(!currentLine->empty()){
            string *userID = new string;
            string *postID = new string;
            string *postContent = new string;
            string *postDate = new string;

            stringstream currentLineSS(*currentLine);
            getline(currentLineSS, *userID, '\t'); //Gets the user ID first from this line
            getline(currentLineSS, *postID, ' '); //Dummy getline to skip the post ID
            getline(currentLineSS, *postContent); //Need to get the rest of the line and cut off when we first encounter a digit
                //If we see a digit, then we have clearly managed to get the post content

            int *postContentEnd = new int;
            for(int i=0;i<postContent->length();i++){
                if(isdigit((*postContent)[i])){
                    *postContentEnd = i - 1; //Want to cut off the space/tab before this too
                    break;
                }
            }
            *postDate = postContent->substr(*postContentEnd+1, postContent->length());
            *postContent = postContent->substr(0, *postContentEnd);

            //Updating the new line in the database
            newDatabase << *userID << " " << *postID << " " << *postContent << " " << *postDate << endl;         

            //Cleaning up the dynamic variables here
            delete userID; delete postID; delete postContent; delete postDate;
            delete postContentEnd;
        }  
    }
    //Renaming the new file to be the same as the old, effectively updating the same file
    close();
    newDatabase.close();
    remove(postFileName.c_str());
    rename("temp.txt", postFileName.c_str());
    //Pointer clean-up
    delete currentLine;
}

//Iterates across the users vector to find what we are looking for
User& ReadPosts::nextUser(){
    if(userIT == users.end()){
        //Should set the thing to start at the beginning again and return the first value
        userIT = users.begin();
    }
    else userIT++;
    return *userIT;
}

 pair<const string, string>& ReadPosts::addPost(int userID, string postContent, string postFileName){
    auto it = posts.insert(pair<string, string>(to_string(userID), postContent));
    //The new post that we just added should be at the end of the multimap, so we just return that
    //I should probably write this to the postfile also
    int *newPostID = new int; //Used to generate a random 10 digit ID
    *newPostID = rand() % 10000000000;
    if(*newPostID < 9000000000) *newPostID += 1000000000;
    //I need to get the current time and store this in a string
    
    time_t timestamp; //Will store time in most basic format
    char output[50]; //Stores the time as a string in a character buffer
    struct tm * datetime; //Stores time as date and time format, rather than perhaps ticks

    time(&timestamp);
    datetime = localtime(&timestamp); //Converts the time into local time for the server

    strftime(output, 50, "%F %T", datetime); //Should store time in output in format %Y-%m-%d %H:%M:%S
    //Now, I'll want to try to convert this to string or input directly into the file

    string formattedTime(output); //converts this time to a string
    postfile.close(); //To prevent clashes with ifstream and ofstream perhaps
    ofstream writer(postFileName, ios::app);
    if(writer){
        writer << endl << userID << " " << *newPostID << " " << postContent << " " << formattedTime;
        writer.close();
    } 
    else{
        //Fail to open the writer
        cout << "Failed to successfully write the new post to the database" << endl;
    }


    return *it;
 }

 void ReadPosts::initialiseUserScores(User& user){
    for(multimap<string, string>::iterator it = posts.begin(); it != posts.end(); it++){
        if(to_string(user.getRegNo()) == it->first){
            //If this post was written by the user
            user.addScore(100, it->second); //By default, each post should start with a reputation score of 100
        }
    }
 }

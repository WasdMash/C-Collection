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
        getline(currentLineSS, cur_userID, "\t"); //Gets the user ID first from this line
        getline(currentLineSS, cur_user_post, " "); //Dummy getline to skip the post ID
        getline(currentLineSS, cur_user_post); //Need to get the rest of the line and cut off when we first encounter a digit
            //If we see a digit, then we have clearly managed to get the post content

        int *postContentEnd = new int;
        for(int i=0;i<strlen(cur_user_post);i++){
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

string ReadPosts::findAuthor(const string &originalPost){
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

pair<string, string>& ReadPosts::findPost()
{
    // to be implemented by you
    // Return the post string that is randomly found in the multimap
    int postRange = distance(posts.begin(), posts.end());
    if(postRange > 0){
        //Do stuff becaause the posts multipmap isn't empty
        int randIndex = rand() % postRange; //Should in theory return a random integer between 0 and range-1
        multimap<string, string>::iterator it;
        advance(it, randIndex); //Advances the it iterator by randIndex times 
        //I should return the post from this iterator which should be it->second
        return it;
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
    
    //I will need an iterator to store all of the posts from a user keyed by their user ID
    pair<multimap<string, string>::iterator, multimap<string, string>::iterator> ip;

    //This will be the sub-range of all posts in the multimap with a ->first value of userID
        /*
            @param posts.begin(): Forward iterator to the first element in the range.
            @param posts.end(): Forward iterator to the last element in the range.
            @param userID: Value of the subrange to search for in the range.
        */
    ip = equal_range(posts.begin(), posts.end(), userID);
    //ip.first will represent a pointer to the first userID-post pair in the subrange
    //Using a ->second on this should return the post part of this pair, which is what we are looking for
    try{
        //If the string is empty, it won't trigger an error but won't be what we want
        if(ip.first->second != "") return ip.first->second;
    }
    catch(...){
        //If we don't even have a suitable post, just return an empty string
        return "";
    }
    
}

void ReadPosts::moderatePost(pair<string, string>& post,  string blacklistName, string postFileName){
    ofstream blacklist(blacklistName); //This is the file from which we shall read all of our banned words/phrases line by line
    string *currentBadWord = new string;
    while(getline(blacklist, *currentBadWord)){
        //Fetches the current naughty word/phrase

        //Check if the naughty is found within the post
        int foundBanPhrase = tolower(post.second).find(tolower(*currentBadWord));
        if(foundBanPhrase != string::npos){
            //We have found a bad word

            //Don't forget to find the user with the same regNO and increment their number of moderated posts
            for(vector<User>::iterator it=users.begin(); it != users.end(); it++){
                if(to_string(it->getRegNo()) == *userID){
                    //We have found the user who triggered a moderation in their posts
                        //Therefore, let's punish them
                        it->updatedModeratedPosts();
                        it->loseReputation(post, min(100, strlen(*currentBadWord)));
                }
            }

            int endIndex = foundBanPhrase + strlen(*currentBadWord); //Need to know when to stop printing Xs
            string moderatedPost = post.second.substr(0, foundBanPhrase); //The start part of the unmoderated post before naughty word
            for(int i=0; i<strlen(*currentBadWord); i++){
                if(*currentBadWord[i] != " ") moderatedPost += "X"; //censoring the bad word here, of course
                else moderatedPost += " "; //Want to make it clear that we aren't just censoring one big word
            }
            //Adding the rest of the string back to censor only part of it
            moderatedPost += post.second.substr(endIndex, strlen(post.second));
            //Adding the cute #moderatedpost tag at the end
            moderatedPost += " #moderatedpost";

            //Don't forget to come back to this and update the score of this user's post
                //Would be a lot easier to do once I've made this an iterable container

            //Should updated the original post to be later updated in the text file
            post.second = moderatedPost;
        }
    }
    delete currentBadWord;
    //At this point, the text file should be updated accordingly
}

void ReadPost::updateTextFile(){
    postfile.seekg(0); //Setting the postFile back to the beginning
    ofstream newDatabase("temp.txt"); //Temporary file to write everything into
    string *currentLine = new string;

    while(getline(postfile, *currentLine)){
        //Want to avoid errors caused by the newline character on the last line of the file
        if(strlen(*currentLine) > 1){
                //Check for our newly moderated post in the text file
            if(currentLine->find(post.first) != string::npos && currentLine->find(post.second) != string::npos){
                //Perfect, we have found the right user and the right post content, meaning we've found the right post
                string *userID = new string;
                string *postID = new string;
                string *postContent = new string;
                string *postDate = new string;

                stringstream currentLineSS(*currentLine);
                getline(currentLineSS, *userID, "\t"); //Gets the user ID first from this line
                getline(currentLineSS, *postID, " "); //Dummy getline to skip the post ID
                getline(currentLineSS, *postContent); //Need to get the rest of the line and cut off when we first encounter a digit
                    //If we see a digit, then we have clearly managed to get the post content

                int *postContentEnd = new int;
                for(int i=0;i<strlen(*postContent);i++){
                    if(isdigit(*postContent[i])){
                        *postContentEnd = i - 1; //Want to cut off the space/tab before this too
                        break;
                    }
                }
                *postDate = postContent->substr(*postContentEnd+1, strlen(*postContent));
                *postContentEnd = postContent->substr(0, *postContentEnd);

                //Updating the new line in the database
                newDatabase << *userID << " " << *postID << " " << post.second << " " << *postDate << endl;         

                //Cleaning up the dynamic variables here
                delete userID; delete postID; delete postContent; delete postDate;
                delete postContentEnd;
            }
            else{
                //This is just a regular line in the file to be copied over to the new file
                newDatabase << *currentLine;
            }
        }  
    }
    //Renaming the new file to be the same as the old, effectively updating the same file
    postFile.close();
    newDatabase.close();
    remove(postFileName.c_str());
    rename("temp.txt", postFileName.c_str());
    //Pointer clean-up
    delete currentLine;
}

//Iterates across the users vector to find what we are looking for
User& ReadPost::nextUser(){
    if(userIT == users.end()){
        //Should set the thing to start at the beginning again and return the first value
        userIT = users.begin();
    }
    else userIT++;
    return *userIT;
}

 pair<string, string>& ReadPosts::addPost(int userID, string postContent){
    posts.insert(pair<string, string>(to_string(userID), postContent));
    //The new post that we just added should be at the end of the multimap, so we just return that
    return *(posts.end());
 }

/**
 * ReadPosts Interface for CE221 assignment 2
 *
 * This header defines:
 * - A ReadPosts class that:
 *   - Reads a large text file of platform posts.
 *   - Each record in the file is expected to have the format:
 *     userID postID post_content date/time
 *   - In this simplified version, a "Post" is just a string representing the entire post content
 *     concatenated with postID and datetime as desired.
 *   - Stores posts in a multimap keyed by userID.
 *   - Provides a findPost() function to select a random post.
 *   - Terminates gracefully if the file cannot be opened.
 */

#ifndef READPOSTS_H
#define READPOSTS_H

#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <cstdlib> // For rand(), srand()
#include <vector>
#include "User.h"

using namespace std;

class ReadPosts
{
public:
    /**
     * Constructor:
     * Attempts to open the file specified by filename.
     * If the file cannot be opened, print an error and terminate the program.
     *
     * @param filename - a C-string specifying the file name.
     */
    ReadPosts(const char *filename);

    /**
     * Closes the file if open.
     */
    void close();

    /**
     * Reads all posts from the file and stores them into the 'posts' multimap.
     * The expected format per line:
     *   userID postID post_content date/time
     *
     * Example:
     *   user123 456 "Hello world!" 2024-01-12T12:34:56
     *
     * For simplicity, we will assume post_content does not contain spaces.
     * The "Post" here will be a single string that you construct from postID, post_content,
     * and datetime. For instance, you might store something like:
     *   postID + " " + post_content + " " + datetime
     */
    void readAllPosts();

    /**
     * Selects a random post from the 'posts' multimap and returns it as a string.
     * If no posts are available, handle gracefully (e.g., return an empty string or print an error).
     *
     * @return A randomly selected post from the data structure.
     */
    pair<string, string>& findPost();

    /**
     * Retrieves a post for the given userID.
     * Returns the first post found for that user, or an empty string if none is found.
     *
     * @param userID - the user ID for which we want to retrieve a post
     * @return A post associated with the given userID, or empty string if not found.
     */
    string getPost(const string &userID) const;

    /*
    *   Gets a post written by an unknown user
    *    Searches through the posts multimap until the post is found
    *    
    *   * @return the user ID of the person who wrote the post
    */
   string findAuthor(const string &originalPost) const;

   /*
        Takes a post and the blacklist file name and then scans the blacklist
        Replaces all banned words/phrases in post content with # and then writes this to the post content file
        Adds a #moderatedPost tag on the end of the post
   */

  void moderatePost(const pair<string, string>& post, string blacklistName, string postFileName);

  pair<string, string>& addPost(int userID, string postContent);

  User& nextUser(); //used to iterate across and return the next user in the uesrs vector for us to do stuff with

  void addUser(User& newUser){
    users.push_back(newUser);
  }

  vector<User>& getUsers(){
    return users;
  }

  //This function will update the text file storing all of the posts
  void updateTextFile(string postFileName);

  //This function will automatically moderate all of the posts and update the text file accordingly
  void moderateAllPosts(string blacklistName, string postFileName){
    multimap<string, string>::iterator it;
    for(it = posts.begin(); it != posts.end(); it++){
      moderatePost(*it, blacklistName, postFileName);
    }
    updateTextFile(postFileName);
  }

  //Gets the user's scores from the posts multimap and initialises their scores before the rest of the program runs
  void initialiseUserScores(User& user);

private:
    ifstream postfile;
    multimap<string, string> posts; // Keyed by userID, value is a string representing the post
    vector<User> users;
    vector<User>::iterator userIT = users.end(); //Iterator used to make my ReadPosts class a custom iterable container
    
};

#endif
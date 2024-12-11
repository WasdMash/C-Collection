#include "ReadPost.h"
#include <iostream>
#include <algorithm>  // for distance and advance if needed
#include <cstdlib>    // for rand(), srand()
#include <ctime>      // for time()
#include <sstream>    // for parsing lines

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
    // If post_content can have spaces, you'd need more complex parsing.
    // Insert all posts from file into multimap
}

string ReadPosts::findPost()
{
    // to be implemented by you
    // Return the post string that is randomly found in the multimap
}

string ReadPosts::getPost(const string &userID) const
{
    // to be implemented by you
    // Find posts for the given userID
    // Return the first post found for this user
}

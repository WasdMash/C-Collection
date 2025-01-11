// include your own comments

#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <map>
#include <stdexcept>
#include "Person.h"

using namespace std;

class NoScoreException: public exception
{
    public:
        NoScoreException();
        //Have to call throw first as their functionality as exception handling relies on this throe
        const char *what() const throw(){
			//Replace this message
            return "This user has no scores";
        }
};

class User: public Person
{   public:
            // constructor should initialise name and registration number using arguments
            // and initialise score map to be empty
            User(const string &name, int regNo);

        // method to return registration number
        int getRegNo() const;

        // method to add the score to the map
        void addScore(float score,string twit);

        // method to update the accumulative score map
        // should throw NoScoreException if user has no tweet yet
        bool updateAccumulativeScore(float score);

            //On this post, the user should lose reputation for this post
                //Should be -10 for a reported post and proportional to length of banned word/phrase for other cases
        void loseReputation(string postContent, int reputationLoss);

        bool operator<(const User &other) const;

        bool operator>(const User &other) const;

        void updatedModeratedPosts();

        int getReputation(){
            return accumulative_reputation_score;
        }

        //I need a function which I can use in for_each to update each of the respective scores in reputation_scores
            //And also probably calculate the accumulative and average reputation scores accordingly also
        void updateScores();

        //This'll be the function I'll use inside of updateScores as part of the STL thing
        void addPostScore(pair<string, float> currentPost);

        string writeToFile() const;

        //This method simply resets all moderated posts for this user whenever the blacklist gets cleared
        void resetModeration();

        //Used in for_each to update each individual moderated post
        void resetModeratedPost(pair<string, float>& currentPost);

    private:
	   int regNo;
	   string name;
	   multimap<string,float> reputation_scores;  // scores map, with each in range 0.0 to 100.0, and a tweet
	   float accumulative_reputation_score; 
	   float average_reputation_score;
       int numOfModeratedPosts; 

    // friend function to output details of user to stream
    // output to be defined and formated by you
    // if the user has no scores "has no scores" should be output instead of the scores
    friend ostream& operator<<(ostream &str, const User &s);
};

#endif

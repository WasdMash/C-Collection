#include "User.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream> //Only needed to convert float to string

using namespace std;

// Constructor for the User class
User::User(const string &name, int regNo) : Person(name), regNo(regNo), accumulative_reputation_score(0), average_reputation_score(0), numOfModeratedPosts(0) {}

// Getter for registration number
int User::getRegNo() const{
    return regNo;
}

// Method to add a score
void User::addScore(float score, string twit) {
    reputation_scores.emplace(twit, score);
    if(!updateAccumulativeScore(score)){
        //Output an error message saying that there are no reputation scores to update
        cout << "There are no reputation scores to update" << endl;
            //Should probably throw an exception here to quit the for_Each
    }
}

// Method to lose reputation
void User::loseReputation(const string postContent, int reputationLoss) {
    auto it = reputation_scores.find(postContent);
    if (it != reputation_scores.end()) {
        it->second -= reputationLoss;
    }
}

// Update accumulative score and average score
bool User::updateAccumulativeScore(float score) {
    try {
        if (reputation_scores.empty()) {
            throw runtime_error("No posts available for calculating scores.");
        }
        accumulative_reputation_score += score;
        average_reputation_score = accumulative_reputation_score / reputation_scores.size();
        return true;
    } catch (const runtime_error &e) {
        cerr << e.what() << endl;
        return false;
    }
}

// Increment the number of moderated posts
void User::updatedModeratedPosts() {
    ++numOfModeratedPosts;
}

// Overloaded output operator
ostream &operator<<(ostream &os, const User &user) {
    os << "User: " << user.name << " (Reg#: " << user.regNo << ")\n"
       << "Accumulative Reputation: " << user.accumulative_reputation_score << "\n"
       << "Average Reputation per Post: " << user.average_reputation_score << "\n"
       << "Number of Moderated Posts: " << user.numOfModeratedPosts << "\n";
    return os;
}

// Comparison operators for sorting
bool User::operator<(const User &other) const {
    if (accumulative_reputation_score == other.accumulative_reputation_score) {
        return numOfModeratedPosts < other.numOfModeratedPosts;
    }
    return accumulative_reputation_score < other.accumulative_reputation_score;
}

bool User::operator>(const User &other) const {
    return !(*this < other);
}

void User::updateScores(){
    //This should update the user values
    average_reputation_score = 0.0;
    accumulative_reputation_score = 0.0; //Should reset the reputation scores to prevent over-exaggerated numbers
    for_each(reputation_scores.begin(), reputation_scores.end(), [this](const pair<string, float>& currentPost) {
                      this->addPostScore(currentPost);
                  });
}

void User::addPostScore(const pair<string, float>& currentPost){
    if(!updateAccumulativeScore(currentPost.second)){
        //Output an error message saying that there are no reputation scores to update
        cout << "There are no reputation scores to update" << endl;
            //Should probably throw an exception here to quit the for_Each
    }
}

string User::writeToFile() const {
    //I'm using this to write the user's values to a text file
    stringstream floatConvert;
    floatConvert << average_reputation_score;
    string output = to_string(regNo) + string(" ") + name + to_string(accumulative_reputation_score) + string(" ") + string(floatConvert.str());
    floatConvert.clear();
    return output;
}

//This function can be called from outside
void User::resetModeration(){
    numOfModeratedPosts = 0;
    for(vector<string,float>::iterator currentPost = reputation_scores.begin(); currentPost != reputation_scores.end(); currentPost++){
            if(currentPost->first.substr(currentPost->first.length() - 14) == "#moderatedpost"){
            currentPost->first = currentPost->first.substr(currentPost.first.length() - 14);
            currentPost->second = 100;
        }
    }
    updateScores();
}


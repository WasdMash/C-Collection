#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>

using namespace std;

class Member{
    public:
        //Trying a one-line constructor like used in Lab 2
        //This neat line should use C++11 to create an empty object
        Member(string name, int age, string membershipID, vector<string> borrowedBooks);

        friend ostream& operator<<(ostream &os, const Member& other);

        string getName(){
            return name;
        };

    private:
        string name;
        int age;
        string membershipID;
        vector<string> borrowedBooks;
       
};

#endif
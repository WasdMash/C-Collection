#ifndef MEMBER_H
#define MEMBER_H

#include <string>

using namespace std;

class Member{
    public:
        //Trying a one-line constructor like used in Lab 2
        Member(string name, int age, string membershipID, string[] borrowedBooks);

    private:
        string name;
        int age;
        string membershipID;
        string[] borrowedBooks;
        
}

#endif
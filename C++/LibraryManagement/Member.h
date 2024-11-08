#ifndef MEMBER_H
#define MEMBER_H

#include <string>

using namespace std;

class Member{
    public:
        //Trying a one-line constructor like used in Lab 2
        Member();
        Member(string name, int age, string membershipID, string[] borrowedBooks);

        ostream& operator<<(ostream &os, const Member &other)
        {
            os << "Your age is " << other.age << endl
            << "Your membership ID is " << other.membershipID << "." << endl
            "Your borrowed books are: " << endl;
   
            if(arr != 0){
                int size = sizeof(borrowedBooks) / sizeof(borrowedBooks[0]);
                for(int i=0;i<size<i++){
                    //Could come back to this later to manually add the quotation marks to the book titles
                    os << " - " << borrowedBooks[i] << endl;
                }
            }

            return os;
        }

        void getName(){
            return name;
        }

    private:
        string name;
        int age;
        string membershipID;
        string[] borrowedBooks;

    
        
}

#endif
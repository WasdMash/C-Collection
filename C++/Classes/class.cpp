#include <iostream>

using namespace std;

class Fighter{
    private:
        //This is where I should put my private attributes and methods
        string name;
        int health;
        static int count; //This exists in the class itself and can be changed outside an instance of the class
    public:
        //This is where I put my public methods and attributes
        Fighter(int playerNum); //This is the consutrctor - runs when the instance of the class is first created
        ~Fighter(); //This is the destructor - runs when the instance of the class is about to be deleted
        getPlayerNum();

        //Example of operator overloading - we are overloading the > operator
        bool operator>(const Fighter &other) const;

}; //Don't forget the semi-colon after the class definition

Fighter::Fighter(int playerNum){
    name = "Player" + playerNum.to_string();
    this->health = 100; //exact same as health=100;
        //Just clarifies that we are changing the values of this instance of the class
    count++;
}

//This destructor gets called after the last reference of the instance of this class int he code
Fighter::~Fighter(){
    printf(name+" has died. Skill issue in my opinion");
    count--;
}

Fighter::getPlayerNum(){
    return name;
}

bool Fighter::operator>(const Fighter &other) const{
    return this.health > other.health;
}
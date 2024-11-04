#include <iostream>
#include "Fighter.h"

using namespace std;

//This destructor gets called after the last reference of the instance of this class int he code
Fighter::~Fighter(){
    printf(name+" has died. Skill issue in my opinion");
    count--;
}

Fighter::getPlayerNum(){
    return name;
}

//Overloading the > operator
bool Fighter::operator>(const Fighter &other) const{
    return this.health > other.health;
}

//Converts the fighter's details into a string
Fighter::operator string() const{
    string tempString;
    tempString += "Name: " + name + " Health: " + to_String(health);
    return tempString;
}

/*
    ostream& operator<<(ostream &outputStream, const Fighter &other){

}
*/
